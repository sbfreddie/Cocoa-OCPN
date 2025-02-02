/***************************************************************************
 *
 * Project:  OpenCPN Weather Routing plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2014 by Sean D'Epagnier                                 *
 *   sean@depagnier.com                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 ***************************************************************************/

#include <wx/wx.h>

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "weather_routing_pi.h"
#include "Utilities.h"
#include "Boat.h"
#include "SwitchPlanDialog.h"
#include "BoatDialog.h"

enum {spNAME, spETA};

BoatDialog::BoatDialog(wxWindow *parent, wxString boatpath)
    : BoatDialogBase(parent), m_boatpath(boatpath), m_PlotScale(0)
{
    m_Boat.OpenXML(m_boatpath);
    m_SelectedSailPlan = 0;

    m_lBoatPlans->InsertColumn(spNAME, _("Name"));
    m_lBoatPlans->InsertColumn(spETA, _("Eta"));
    RepopulatePlans();

    m_sDisplacement->SetValue(m_Boat.displacement_tons);
    m_sLWL->SetValue(m_Boat.lwl_ft);
    m_sLOA->SetValue(m_Boat.loa_ft);

    m_sFrictionalDrag->SetValue(m_Boat.frictional_drag * 1000.0);
    m_sWakeDrag->SetValue(m_Boat.wake_drag * 100.0);

    m_SelectedSailPlan = 0;
    m_lBoatPlans->SetItemState(m_SelectedSailPlan, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    m_sEta->SetValue(m_Boat.Plans[m_SelectedSailPlan].eta * 1000.0);

    UpdateStats();
    UpdateVMG();
    
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T( "/PlugIns/WeatherRouting/BoatDialog" ) );
}

BoatDialog::~BoatDialog()
{
}

void BoatDialog::OnMouseEventsPlot( wxMouseEvent& event )
{
    if(event.Leaving()) {
        m_stTrueWindAngle->SetLabel(_("N/A"));
        m_stTrueWindKnots->SetLabel(_("N/A"));
        m_stApparentWindAngle->SetLabel(_("N/A"));
        m_stApparentWindKnots->SetLabel(_("N/A"));
        m_stBoatAngle->SetLabel(_("N/A"));
        m_stBoatKnots->SetLabel(_("N/A"));
    }

    if(!m_PlotScale)
        return;

    wxPoint p = event.GetPosition();
    wxSize s = m_PlotWindow->GetSize();

    /* range + to - */
    double x = (double)p.x - s.x/2;
    double y = (double)p.y - s.y/2;

    /* range +- */
    x /= m_PlotScale;
    y /= m_PlotScale;

#if 0
    switch(m_cPlotAxis->GetSelection()) {
    case 0: /* Boat */
    {
#endif
        double B = rad2posdeg(atan2(x, -y));
        double W = -B, VW = m_sWindSpeed->GetValue();

        double VB = m_Boat.Plans[m_SelectedSailPlan].Speed(B, VW);

        m_stBoatAngle->SetLabel(wxString::Format(_T("%03.0f"), B));
        m_stBoatKnots->SetLabel(wxString::Format(_T("%.1f"), VB));

        int newmousew = round(B);
        if(newmousew != m_MouseW) {
            m_MouseW = newmousew;
            m_PlotWindow->Refresh();
        }

        m_stTrueWindAngle->SetLabel(wxString::Format(_T("%03.0f"), W));
        m_stTrueWindKnots->SetLabel(wxString::Format(_T("%.1f"), VW));

        double VA = BoatPlan::VelocityApparentWind(VB, deg2rad(W), VW);
        double A = rad2posdeg(BoatPlan::DirectionApparentWind(VA, VB, deg2rad(W), VW));

        m_stApparentWindAngle->SetLabel(wxString::Format(_T("%03.0f"), A));

        m_stApparentWindKnots->SetLabel(wxString::Format(_T("%.1f"), VA));

#if 0
    } break;
    case 1: /* True Wind */
    {
        x *= m_PlotScale, y *= m_PlotScale;
        double W = rad2posdeg(atan2(x, -y)), VW = hypot(x, y);
        m_stTrueWindAngle->SetLabel(wxString::Format(_T("%03.0f"), W));
        m_stTrueWindKnots->SetLabel(wxString::Format(_T("%.1f"), VW));

        double VB = m_Boat.Speed(0, W, VW);
        double B = -W;

        m_stBoatAngle->SetLabel(wxString::Format(_T("%03.0f"), B));
        m_stBoatKnots->SetLabel(wxString::Format(_T("%.1f"), VB));

        double VA = BoatSpeed::VelocityApparentWind(VB, W, VW);
        double A = BoatSpeed::DirectionApparentWind(VA, VB, W, VW);

        m_stApparentWindAngle->SetLabel(wxString::Format(_T("%03.0f"), A));
        m_stApparentWindKnots->SetLabel(wxString::Format(_T("%.1f"), VA));

    } break;
    case 2: /* Apparent Wind */
    {

    } break;
    }
#endif
}

void BoatDialog::OnPaintPlot(wxPaintEvent& event)
{
    wxWindow *window = dynamic_cast<wxWindow*>(event.GetEventObject());
    if(!window)
        return;

#if 0        
        switch(m_cPlotAxis->GetSelection()) {
        case 0: /* boat */
        {
            points[i] = wxPoint(1000*VB*sin(deg2rad(B)), -1000*VB*cos(deg2rad(B)));
        } break;
        case 1: /* true wind */
        {
            
        } break;
        case 2: /* apparent wind */
        {
        } break;
        }
#endif

    wxPaintDC dc(window);
    dc.SetBackgroundMode(wxTRANSPARENT);

    int w, h;
    m_PlotWindow->GetSize( &w, &h);
    m_PlotScale = (w < h ? w : h)/1.8;
    double maxVB = 0;

    int VW = m_sWindSpeed->GetValue();

    int W, i;
    /* plot scale */
    for(W = 0, i=0; W<DEGREES; W += DEGREE_STEP, i++) {
        double VB = m_Boat.Plans[m_SelectedSailPlan].Speed(W, VW);
        if(VB > maxVB)
            maxVB = VB;
    }
    
    dc.SetPen(wxPen(wxColor(0, 0, 0)));
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    dc.SetTextForeground(wxColour(0, 55, 75));

    if(maxVB <= 0) maxVB = 1; /* avoid lock */
    double Vstep = ceil(maxVB / 5);
    maxVB += Vstep;

    m_PlotScale = m_PlotScale / (maxVB+1);

    /* polar circles */
    for(double V = Vstep; V <= maxVB; V+=Vstep) {
        dc.DrawCircle(w/2, h/2, V*m_PlotScale);
        dc.DrawText(wxString::Format(_T("%.0f"), V), w/2, h/2+(int)V*m_PlotScale);
    }

    /* polar meridians */
    dc.SetTextForeground(wxColour(0, 0, 155));
    for(double B = 0; B < 360; B+=15) {
        double x = maxVB*m_PlotScale*sin(deg2rad(B));
        double y = maxVB*m_PlotScale*cos(deg2rad(B));
        if(B < 180)
            dc.DrawLine(w/2 - x, h/2 + y, w/2 + x, h/2 - y);

        wxString str = wxString::Format(_T("%.0f"), B);
        int sw, sh;
        dc.GetTextExtent(str, &sw, &sh);
        dc.DrawText(str, w/2 + .9*x - sw/2, h/2 - .9*y - sh/2);
    }

    /* vmg */
    int px, py;
    dc.SetPen(wxPen(wxColor(255, 0, 255), 2));

    double s = maxVB*m_PlotScale;
    SailingVMG vmg = m_Boat.Plans[m_SelectedSailPlan].GetVMG(VW);

    W = vmg.PortTackUpWind;
    px = s*sin(deg2rad(W));
    py = s*cos(deg2rad(W));
    dc.DrawLine(w/2, h/2, w/2 + px, h/2 - py);

    W = vmg.StarboardTackUpWind;
    px = s*sin(deg2rad(W));
    py = s*cos(deg2rad(W));
    dc.DrawLine(w/2, h/2, w/2 + px, h/2 - py);

    dc.SetPen(wxPen(wxColor(255, 255, 0), 2));

    W = vmg.PortTackDownWind;
    px = s*sin(deg2rad(W));
    py = s*cos(deg2rad(W));
    dc.DrawLine(w/2, h/2, w/2 + px, h/2 - py);

    W = vmg.StarboardTackDownWind;
    px = s*sin(deg2rad(W));
    py = s*cos(deg2rad(W));
    dc.DrawLine(w/2, h/2, w/2 + px, h/2 - py);

    /* boat speeds */
    int lx, ly;
    for(W = 0; W<=DEGREES; W += DEGREE_STEP) {
//        SailingSpeed speed = m_Boat.Plans[m_SelectedSailPlan]->speed[VW][(W%DEGREES)];
        double VB = m_Boat.Plans[m_SelectedSailPlan].Speed(W, VW);

        dc.SetPen(wxPen(wxColor(255, 0, 0), 2));

        int px =  m_PlotScale*VB*sin(deg2rad(W)) + w/2;
        int py = -m_PlotScale*VB*cos(deg2rad(W)) + h/2;

        if(W > 0)
            dc.DrawLine(lx, ly, px, py);
        lx = px, ly = py;

#if 0
        if(W == m_MouseW) {
            int B = speed.b;
            SailingSpeed speedB = m_Boat.Plans[m_SelectedSailPlan]->speed[VW][B];
            double BVB = speedB.VB;
            int pxb =  m_PlotScale*speed.w*BVB*sin(deg2rad(B)) + w/2;
            int pyb = -m_PlotScale*speed.w*BVB*cos(deg2rad(B)) + h/2;

            dc.SetPen(wxPen(wxColor(0, 0, 255), 2));
            dc.DrawLine(w/2, h/2, pxb, pyb);

            if(speed.w < 1) {
                dc.SetPen(wxPen(wxColor(0, 255, 0), 2));
                dc.DrawLine(pxb, pyb, px, py);
            }
        }
#endif
    }
}

void BoatDialog::OnUpdateWindSpeed( wxSpinEvent& event )
{
    UpdateVMG();
    m_PlotWindow->Refresh();
}

void BoatDialog::OnOpen ( wxCommandEvent& event )
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T( "/PlugIns/WeatherRouting/BoatDialog" ) );
    
    wxString path;
    pConf->Read ( _T ( "Path" ), &path, weather_routing_pi::StandardPath());

    wxFileDialog openDialog
        ( this, _( "Select Polar" ), path, wxT ( "" ),
          wxT ( "Boat polar files (*.xml, *.cvs)|*.XML;*.xml;*.CSV;*.csv|All files (*.*)|*.*" ),
          wxFD_OPEN  );

    if( openDialog.ShowModal() == wxID_OK ) {
        wxString filename = openDialog.GetPath();
        pConf->SetPath ( _T( "/PlugIns/WeatherRouting/BoatDialog" ) );
        pConf->Write ( _T ( "Path" ), wxFileName(filename).GetPath() );
        
        wxString error = m_Boat.OpenXML(filename);
        if(error.empty())
            RepopulatePlans();
        else {
            wxMessageDialog md(this, error, _("OpenCPN Weather Routing Plugin"),
                               wxICON_ERROR | wxOK );
            md.ShowModal();
            return;
        }

        UpdateStats();
        UpdateVMG();
        m_PlotWindow->Refresh();
    }
}

void BoatDialog::LoadCSV()
{
    wxString filename = m_fpCSVPath->GetPath();

    BoatPlan &plan = m_Boat.Plan(m_SelectedSailPlan);
    BoatSpeedTable table;
    if(table.Open(filename.mb_str(),
                  plan.wind_speed_step, plan.wind_degree_step)) {
        plan.csvFileName = filename;
        plan.SetSpeedsFromTable(table);
        RepopulatePlans();
    } else {
        wxMessageDialog md(this, _("Failed reading csv: ") + filename,
                           _("OpenCPN Weather Routing Plugin"),
                           wxICON_ERROR | wxOK );
        md.ShowModal();
        return;
    }
    
    UpdateStats();
    UpdateVMG();
    m_PlotWindow->Refresh();
}

void BoatDialog::Save()
{
    wxString error = m_Boat.SaveXML(m_boatpath);
    if(error.empty())
        EndModal(wxID_OK);
    else {
        wxMessageDialog md(this, error, _("OpenCPN Weather Routing Plugin"),
                           wxICON_ERROR | wxOK );
        md.ShowModal();
    }
}

void BoatDialog::OnSaveAs ( wxCommandEvent& event )
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T( "/PlugIns/WeatherRouting/BoatDialog" ) );
    
    wxString path;
    pConf->Read ( _T ( "Path" ), &path, weather_routing_pi::StandardPath());
    
    wxFileDialog saveDialog( this, _( "Select Polar" ), path, wxT ( "" ),
                            wxT ( "Boat files (*.xml)|*.XML;*.xml|All files (*.*)|*.*" ),
                            wxFD_SAVE | wxFD_OVERWRITE_PROMPT );

    if( saveDialog.ShowModal() == wxID_OK ) {
        wxString filename = wxFileDialog::AppendExtension(saveDialog.GetPath(), _T("*.xml"));

        pConf->SetPath ( _T( "/PlugIns/WeatherRouting/BoatDialog" ) );
        pConf->Write ( _T ( "Path" ), wxFileName(filename).GetPath() );
        
        m_boatpath = filename;
        Save();
    }
}

void BoatDialog::OnClose ( wxCommandEvent& event )
{
    EndModal(wxID_CANCEL);
}

void BoatDialog::OnSaveCSV ( wxCommandEvent& event )
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T( "/PlugIns/WeatherRouting/BoatDialog" ) );
    
    wxString path;
    pConf->Read ( _T ( "CSVPath" ), &path, weather_routing_pi::StandardPath());
    
    wxFileDialog saveDialog( this, _( "Select Polar" ), path, wxT ( "" ),
                             wxT ( "Boat Polar files (*.cvs)|*.CSV;*.csv|All files (*.*)|*.*" ), wxFD_SAVE  );
    if( saveDialog.ShowModal() == wxID_OK ) {
        wxString filename = saveDialog.GetPath();
        pConf->SetPath ( _T( "/PlugIns/WeatherRouting/BoatDialog" ) );
        pConf->Write ( _T ( "CSVPath" ), wxFileName(filename).GetPath() );

        BoatSpeedTable table = m_Boat.Plans[m_SelectedSailPlan].CreateTable
            (3, 3);
        if(!table.Save(saveDialog.GetPath().mb_str())) {
            wxMessageDialog md(this, _("Failed saving boat polar to csv"),
                               _("OpenCPN Weather Routing Plugin"),
                               wxICON_ERROR | wxOK );
            md.ShowModal();
        }
    }
}

void BoatDialog::OnPolarCSVFile( wxFileDirPickerEvent& event )
{
    LoadCSV();
}

void BoatDialog::OnRecompute()
{
    StoreBoatParameters();
    Compute();
    UpdateStats();
}

void BoatDialog::OnOptimizeTacking ( wxCommandEvent& event )
{
    m_Boat.Plans[m_SelectedSailPlan].OptimizeTackingSpeed();
    m_PlotWindow->Refresh();
}

void BoatDialog::OnResetOptimalTackingSpeed( wxCommandEvent& event )
{
    m_Boat.Plans[m_SelectedSailPlan].ResetOptimalTackingSpeed();
    m_PlotWindow->Refresh();
}

void BoatDialog::OnRecomputeDrag( wxCommandEvent& event )
{
    StoreBoatParameters();
    m_Boat.RecomputeDrag();
    m_sFrictionalDrag->SetValue(1000.0 * m_Boat.frictional_drag);
    m_sWakeDrag->SetValue(100.0 * m_Boat.wake_drag);
    Compute();
}

void BoatDialog::OnDragInfo( wxCommandEvent& event )
{
    wxMessageDialog md(this, _("\
Drag is both frictional and wave based\n\
This can be computed based on boat values above then modified manually.\n\
With proper settings hull speed will be achieved, but also break into planing mode possible.\n\
A value 0 zero means no wake, where 100 is heaviest displacement.\n\
This also takes into account the different harmonics of wakes before hull speed is reached, \
so resulting boat polar may appear bumpy.\n"),
                       _("Drag Computation"),
                       wxICON_INFORMATION | wxOK );
    md.ShowModal();
}

void BoatDialog::OnSailPlanSelected( wxListEvent& event )
{
    m_SelectedSailPlan = event.GetIndex();
    m_sEta->SetValue(m_Boat.Plans[m_SelectedSailPlan].eta * 1000.0);
    m_sLuffAngle->SetValue(m_Boat.Plans[m_SelectedSailPlan].luff_angle);
    m_cbWingWingRunning->SetValue(m_Boat.Plans[m_SelectedSailPlan].wing_wing_running);

    bool c = m_Boat.Plans[m_SelectedSailPlan].computed;
    m_sbComputation->ShowItems(c);
    m_sbCSV->ShowItems(!c);
    m_pPolarConfig->Fit();
    Fit();

    m_PlotWindow->Refresh();
}

void BoatDialog::OnPolarMode( wxCommandEvent& event )
{
    bool c = m_rbComputed->GetValue();
    
    m_Boat.Plans[m_SelectedSailPlan].computed = c;
    m_sbComputation->ShowItems(c);
    m_sbCSV->ShowItems(!c);
    m_pPolarConfig->Fit();
    Fit();
}

void BoatDialog::OnEta( wxScrollEvent& event )
{
    StoreBoatParameters();
    Compute();
}

void BoatDialog::OnNewBoatPlan( wxCommandEvent& event )
{
    wxString np = _("New Plan");
    m_SelectedSailPlan = m_lBoatPlans->InsertItem(m_lBoatPlans->GetItemCount(), np);
    m_Boat.Plans.push_back(BoatPlan(np, m_Boat));
    m_lBoatPlans->SetItemState(m_SelectedSailPlan, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    StoreBoatParameters();
    Compute();
    m_bDeleteBoatPlan->Enable();

    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath ( _T( "/PlugIns/WeatherRouting/BoatDialog" ) );

    wxString path;
    pConf->Read ( _T ( "CSVPath" ), &path, weather_routing_pi::StandardPath());
    m_fpCSVPath->SetPath(path);
}

void BoatDialog::OnDeleteBoatPlan( wxCommandEvent& event )
{
    m_lBoatPlans->DeleteItem(m_SelectedSailPlan);
    m_Boat.Plans.erase(m_Boat.Plans.begin() + m_SelectedSailPlan);

    if(m_Boat.Plans.size() < 2)
        m_bDeleteBoatPlan->Disable();
}

void BoatDialog::StoreBoatParameters()
{
    if(m_SelectedSailPlan < 0 ||
        m_SelectedSailPlan >= (int)m_Boat.Plans.size())
        return;

    BoatPlan &plan = m_Boat.Plans[m_SelectedSailPlan];
    plan.eta = m_sEta->GetValue() / 1000.0;
    plan.luff_angle = m_sLuffAngle->GetValue();
    plan.wing_wing_running = m_cbWingWingRunning->GetValue();

    m_Boat.hulltype = (Boat::HullType)m_cHullType->GetSelection();

    m_Boat.displacement_tons = m_sDisplacement->GetValue();
    m_Boat.lwl_ft = m_sLWL->GetValue();
    m_Boat.loa_ft = m_sLOA->GetValue();
    m_Boat.beam_ft = m_sBeam->GetValue();

    m_Boat.frictional_drag = m_sFrictionalDrag->GetValue() / 1000.0;
    m_Boat.wake_drag = m_sWakeDrag->GetValue() / 100.0;
}

void BoatDialog::RepopulatePlans()
{
    m_lBoatPlans->DeleteAllItems();

    if(m_Boat.Plans.size() == 0) {
        m_Boat.Plans.push_back(BoatPlan(_("Initial Plan"), m_Boat));
        m_Boat.Plans[0].ComputeBoatSpeeds(m_Boat);
    }

    for(unsigned int i=0; i<m_Boat.Plans.size(); i++) {
        wxListItem info;
        info.SetId(i);
        info.SetData(i);
        long idx = m_lBoatPlans->InsertItem(info);
        BoatPlan &plan = m_Boat.Plans[i];
        m_lBoatPlans->SetItem(idx, spNAME, plan.Name);
        m_lBoatPlans->SetItem(idx, spETA, wxString::Format(_T("%.2f"), plan.eta));
    }

    m_lBoatPlans->SetColumnWidth(spNAME, 150);
    m_lBoatPlans->SetColumnWidth(spETA, 60);

    if(m_Boat.Plans.size() > 1)
        m_bDeleteBoatPlan->Enable();
    else
        m_bDeleteBoatPlan->Disable();

    BoatPlan &plan = m_Boat.Plans[m_SelectedSailPlan];

    m_fpCSVPath->SetPath(plan.csvFileName);
    m_stWindSpeedStep->SetLabel
    (wxString::Format(_T("%d"), plan.wind_speed_step));
    m_stWindDegreeStep->SetLabel
    (wxString::Format(_T("%d"), plan.wind_degree_step));
}

void BoatDialog::Compute()
{
    if(m_SelectedSailPlan < 0 ||
        m_SelectedSailPlan >= (int)m_Boat.Plans.size())
        return;

    BoatPlan &plan = m_Boat.Plans[m_SelectedSailPlan];
    plan.ComputeBoatSpeeds(m_Boat);


    UpdateVMG();
    m_PlotWindow->Refresh();
    m_lBoatPlans->SetItem(m_SelectedSailPlan, spETA, wxString::Format(_T("%.3f"),
                                                                       m_sEta->GetValue()/1000.0));
}

void BoatDialog::UpdateVMG()
{
    int VW = m_sWindSpeed->GetValue();
    SailingVMG vmg = m_Boat.Plans[m_SelectedSailPlan].GetVMG(VW);

    m_stBestCourseUpWindPortTack->SetLabel
        (wxString::Format(_T("%d"), vmg.PortTackUpWind));
    m_stBestCourseUpWindStarboardTack->SetLabel
        (wxString::Format(_T("%d"), vmg.StarboardTackUpWind));
    m_stBestCourseDownWindPortTack->SetLabel
        (wxString::Format(_T("%d"), vmg.PortTackDownWind));
    m_stBestCourseDownWindStarboardTack->SetLabel
        (wxString::Format(_T("%d"), vmg.StarboardTackDownWind));
}

void BoatDialog::OnNewSwitchPlanRule( wxCommandEvent& event )
{
    SwitchPlan plan;
    
    plan.Name = m_Boat.Plans[0].Name;
    
    m_Boat.Plans[m_SelectedSailPlan].SwitchPlans.push_back(plan);
    
    int index = m_lSwitchPlans->Append(wxString());
    m_lSwitchPlans->SetSelection(index, true);
    
    m_bEditSwitchBoatPlan->Enable();
    m_bDeleteSwitchBoatPlan->Enable();
    
    OnEditSwitchPlanRule(event);
}

void BoatDialog::OnEditSwitchPlanRule( wxCommandEvent& event )
{
    int index = m_lSwitchPlans->GetSelection();
    if(index < 0)
        return;
    
    BoatPlan &boatplan = m_Boat.Plans[m_SelectedSailPlan];
    SwitchPlan plan = boatplan.SwitchPlans[index];

    if(m_Boat.Plans.size() < 1) {
        wxMessageDialog md(this, _("Cannot edit switch plan since there is no other plan to switch to."),
                           _("Sail Plans"),
                           wxICON_ERROR | wxOK );
        md.ShowModal();
        return;
    }
    
    SwitchPlanDialog dialog(this, plan, m_Boat.Plans);
    if(dialog.ShowModal() == wxID_OK)
        boatplan.SwitchPlans[index] = plan;
    else
        boatplan.SwitchPlans.erase(boatplan.SwitchPlans.begin() + index);
    
    PopulatePlans();
}

void BoatDialog::OnDeleteSwitchPlanRule( wxCommandEvent& event )
{
    int index = m_lSwitchPlans->GetSelection();
    if(index < 0)
        return;
    
    BoatPlan &boatplan = m_Boat.Plans[m_SelectedSailPlan];
    SwitchPlan plan = boatplan.SwitchPlans[index];
    boatplan.SwitchPlans.erase(boatplan.SwitchPlans.begin() + index);
    PopulatePlans();
}

void BoatDialog::PopulatePlans()
{
    BoatPlan &boatplan = m_Boat.Plans[m_SelectedSailPlan];
    
    if(boatplan.SwitchPlans.size() == 0) {
        m_bEditSwitchBoatPlan->Disable();
        m_bDeleteSwitchBoatPlan->Disable();
    }
    
    m_lSwitchPlans->Clear();
    
    for(unsigned int i=0; i<boatplan.SwitchPlans.size(); i++) {
        SwitchPlan plan = boatplan.SwitchPlans[i];
        
        wxString des, a, andstr = _(" and ");
        if(!isnan(plan.MaxWindSpeed))
            des += a + _("Wind Speed > ") + wxString::Format(_("%.0f"), plan.MaxWindSpeed), a = andstr;
        
        if(!isnan(plan.MinWindSpeed))
            des += a + _("Wind Speed < ") + wxString::Format(_("%.0f"), plan.MinWindSpeed), a = andstr;
        
        if(!isnan(plan.MaxWindDirection))
            des += a + _("Wind Direction > ") + wxString::Format(_("%.0f"), plan.MaxWindDirection), a = andstr;
        
        if(!isnan(plan.MinWindDirection))
            des += a + _("Wind Direction < ") + wxString::Format(_("%.0f"), plan.MinWindDirection), a = andstr;
        
        if(!isnan(plan.MaxWaveHeight))
            des += a + _("Wave Height > ") + wxString::Format(_("%.0f"), plan.MaxWaveHeight), a = andstr;
        
        if(!isnan(plan.MinWaveHeight))
            des += a + _("Wave Height < ") + wxString::Format(_("%.0f"), plan.MinWaveHeight), a = andstr;
        
        if(!plan.DayTime) {
            des += a + _("Night Time");
        } else if(!plan.NightTime) {
            des += a + _("Day Time");
        }
        
        des += _(" switch to ");
        des += plan.Name;
        
        m_lSwitchPlans->Append(des);
    }
}

void BoatDialog::UpdateStats()
{
    m_stHullSpeed->SetLabel(wxString::Format(_T("%.3f"), m_Boat.HullSpeed()));
    m_stCapsizeRisk->SetLabel(wxString::Format(_T("%.3f"), m_Boat.CapsizeRisk()));
    m_stComfortFactor->SetLabel(wxString::Format(_T("%.3f"), m_Boat.ComfortFactor()));
    m_stDisplacementLengthRatio->SetLabel(wxString::Format(_T("%.3f"), m_Boat.DisplacementLengthRatio()));
}
