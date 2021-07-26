void Z1Z2_W()
{
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Sat Mar 13 08:29:54 2021) by ROOT version 6.18/04
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",2016,952,538,323);
   Canvas_1->Range(73.64742,73.45764,74.97602,75.00823);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TCutG *cutg = new TCutG("cID_Z1_Z2_Gate0",8);
   cutg->SetVarX("");
   cutg->SetVarY("");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,74.10994,74.73512);
   cutg->SetPoint(1,73.86886,74.39742);
   cutg->SetPoint(2,73.91603,73.89823);
   cutg->SetPoint(3,74.34579,73.71607);
   cutg->SetPoint(4,74.60784,73.85418);
   cutg->SetPoint(5,74.75459,74.48552);
   cutg->SetPoint(6,74.49778,74.7498);
   cutg->SetPoint(7,74.10994,74.73512);
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
