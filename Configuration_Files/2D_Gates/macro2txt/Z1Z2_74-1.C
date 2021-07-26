{
//========= Macro generated from object: cID_Z_AoQ0/
//========= by ROOT version6.18/04
   
   TCutG *cutg = new TCutG("cID_Z_AoQ0",8);
   cutg->SetVarX("");
   cutg->SetVarY("");
   cutg->SetTitle("");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   cutg->SetFillColor(ci);
   cutg->SetFillStyle(3444);

   ci = TColor::GetColor("#ff0000");
   cutg->SetLineColor(ci);
   cutg->SetLineWidth(3);
   cutg->SetPoint(0,74.1168,74.5528);
   cutg->SetPoint(1,72.9694,74.0428);
   cutg->SetPoint(2,74.2098,72.695);
   cutg->SetPoint(3,74.4207,72.9621);
   cutg->SetPoint(4,74.6378,73.6664);
   cutg->SetPoint(5,74.7122,73.9578);
   cutg->SetPoint(6,74.3773,74.4557);
   cutg->SetPoint(7,74.1168,74.5528);
   cutg->Draw("");
}
