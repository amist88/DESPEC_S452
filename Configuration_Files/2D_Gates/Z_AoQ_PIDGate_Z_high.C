void Z_AoQ_PIDGate_Z_high()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Sun Mar  7 13:36:15 2021) by ROOT version 6.18/04
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",258,74,538,323);
   Canvas_1->Range(2.520207,74.14114,2.680921,75.56912);
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
   cutg->SetPoint(0,2.546992,75.20695);
   cutg->SetPoint(1,2.607143,75.33113);
   cutg->SetPoint(2,2.616541,75.24834);
   cutg->SetPoint(3,2.62688,75.24834);
   cutg->SetPoint(4,2.654135,75.12417);
   cutg->SetPoint(5,2.652256,74.5447);
   cutg->SetPoint(6,2.62406,74.37914);
   cutg->SetPoint(7,2.549812,74.62748);
   cutg->SetPoint(8,2.546992,75.20695);
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
