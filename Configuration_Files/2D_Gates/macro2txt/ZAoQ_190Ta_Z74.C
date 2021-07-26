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
   cutg->SetPoint(0,2.62733,74.2405);
   cutg->SetPoint(1,2.63045,73.7083);
   cutg->SetPoint(2,2.6193,73.4626);
   cutg->SetPoint(3,2.60437,73.7083);
   cutg->SetPoint(4,2.60815,74.3019);
   cutg->SetPoint(5,2.61707,74.4759);
   cutg->SetPoint(6,2.62041,74.3838);
   cutg->SetPoint(7,2.62733,74.2405);
   cutg->Draw("");
}
