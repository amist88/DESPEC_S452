void Z_AoQ_PIDGate_Z_high_SC22()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Thu Mar 11 19:00:26 2021) by ROOT version 6.18/04
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",905,146,972,647);
   Canvas_1->Range(2.536471,73.43593,2.697702,74.86235);
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
   cutg->SetPoint(0,2.563343,74.51895);
   cutg->SetPoint(1,2.623569,74.62461);
   cutg->SetPoint(2,2.63277,74.55417);
   cutg->SetPoint(3,2.643226,74.55417);
   cutg->SetPoint(4,2.67083,74.41329);
   cutg->SetPoint(5,2.668739,73.84976);
   cutg->SetPoint(6,2.640717,73.67366);
   cutg->SetPoint(7,2.56627,73.92021);
   cutg->SetPoint(8,2.563343,74.51895);
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
