void Z1Z2_Ta()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Sat Mar 13 08:30:34 2021) by ROOT version 6.18/04
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",2016,952,538,323);
   Canvas_1->Range(72.62484,72.66037,74.06834,74.00488);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TCutG *cutg = new TCutG("cID_Z1_Z2_Gate1",8);
   cutg->SetVarX("");
   cutg->SetVarY("");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,73.16453,73.68933);
   cutg->SetPoint(1,72.86543,73.34177);
   cutg->SetPoint(2,73.11251,72.91189);
   cutg->SetPoint(3,73.54816,72.88445);
   cutg->SetPoint(4,73.78874,73.33262);
   cutg->SetPoint(5,73.82776,73.54299);
   cutg->SetPoint(6,73.53516,73.78079);
   cutg->SetPoint(7,73.16453,73.68933);
   cutg->Draw("alp");
   
   TPaveText *pt = new TPaveText(0.4461567,0.9351869,0.5538433,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("Graph");
   pt->Draw();
   Canvas_1->Modified();
   Canvas_1->cd();
   Canvas_1->SetSelected(Canvas_1);
}
