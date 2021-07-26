void Z_AoQ_PIDGate_Z_low_SC22()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Thu Mar 11 19:01:04 2021) by ROOT version 6.18/04
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",917,125,538,323);
   Canvas_1->Range(2.529288,72.56301,2.689038,73.85591);
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
   cutg->SetPoint(0,2.555913,73.50433);
   cutg->SetPoint(1,2.615191,73.64043);
   cutg->SetPoint(2,2.624736,73.5497);
   cutg->SetPoint(3,2.635285,73.5497);
   cutg->SetPoint(4,2.662413,73.45897);
   cutg->SetPoint(5,2.660403,72.86922);
   cutg->SetPoint(6,2.635788,72.7785);
   cutg->SetPoint(7,2.558927,72.91459);
   cutg->SetPoint(8,2.555913,73.50433);
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
