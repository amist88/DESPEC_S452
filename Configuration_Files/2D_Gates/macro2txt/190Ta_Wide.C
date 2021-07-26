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
   cutg->SetPoint(0,2.47751,74.59);
   cutg->SetPoint(1,2.48659,73.7127);
   cutg->SetPoint(2,2.46934,73.2853);
   cutg->SetPoint(3,2.4536,73.859);
   cutg->SetPoint(4,2.45723,74.6463);
   cutg->SetPoint(5,2.46631,74.6125);
   cutg->SetPoint(6,2.47055,74.5113);
   cutg->SetPoint(7,2.47751,74.59);
   cutg->Draw("");
}
