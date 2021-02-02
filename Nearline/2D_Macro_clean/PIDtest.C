{
//========= Macro generated from object: cID_Z1_AoQ0/
//========= by ROOT version6.16/00
   
   TCutG *cutg = new TCutG("cID_Z1_AoQ0",8);
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
   cutg->SetPoint(0,2.61614,75.1633);
   cutg->SetPoint(1,2.60418,72.1612);
   cutg->SetPoint(2,2.58668,72.5019);
   cutg->SetPoint(3,2.51056,71.7662);
   cutg->SetPoint(4,2.53347,76.1113);
   cutg->SetPoint(5,2.56833,75.7163);
   cutg->SetPoint(6,2.63506,75.5583);
   cutg->SetPoint(7,2.61614,75.1633);
   cutg->Draw("");
}
