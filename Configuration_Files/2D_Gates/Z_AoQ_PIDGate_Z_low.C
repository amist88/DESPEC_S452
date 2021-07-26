void Z_AoQ_PIDGate_Z_low()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Sun Mar  7 13:35:34 2021) by ROOT version 6.18/04
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",258,74,538,323);
   Canvas_1->Range(2.376708,73.29288,2.53709,74.74008);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TCutG *cutg = new TCutG("cID_Z1_AoQ0",9);
   cutg->SetVarX("");
   cutg->SetVarY("");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,2.403438,74.3685);
   cutg->SetPoint(1,2.463314,74.49888);
   cutg->SetPoint(2,2.472581,74.42065);
   cutg->SetPoint(3,2.483273,74.42065);
   cutg->SetPoint(4,2.51036,74.29027);
   cutg->SetPoint(5,2.508221,73.71661);
   cutg->SetPoint(6,2.480421,73.53408);
   cutg->SetPoint(7,2.406289,73.79484);
   cutg->SetPoint(8,2.403438,74.3685);
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
