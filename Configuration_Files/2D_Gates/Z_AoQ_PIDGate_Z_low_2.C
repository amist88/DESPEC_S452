void Z_AoQ_PIDGate_Z_low_2()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Sun Mar  7 13:40:34 2021) by ROOT version 6.18/04
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",1089,74,538,323);
   Canvas_1->Range(2.521453,73.37434,2.676762,74.56341);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TCutG *cutg = new TCutG("cID_Z1_AoQ1",9);
   cutg->SetVarX("");
   cutg->SetVarY("");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,2.635601,74.22368);
   cutg->SetPoint(1,2.56318,74.36523);
   cutg->SetPoint(2,2.550732,74.2803);
   cutg->SetPoint(3,2.547338,73.65745);
   cutg->SetPoint(4,2.603917,73.57252);
   cutg->SetPoint(5,2.612404,73.57252);
   cutg->SetPoint(6,2.62768,73.57252);
   cutg->SetPoint(7,2.650877,73.94056);
   cutg->SetPoint(8,2.635601,74.22368);
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
