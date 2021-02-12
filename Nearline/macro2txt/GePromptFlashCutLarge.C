{
//========= Macro generated from object: cID_Z_AoQ0/
//========= by ROOT version6.16/00
   
   TCutG *cutg = new TCutG("cID_Z_AoQ0",8);
   cutg->SetVarX("");
   cutg->SetVarY("");
   cutg->SetTitle("");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#00ff00");
   cutg->SetFillColor(ci);
   cutg->SetFillStyle(3444);

   ci = TColor::GetColor("#00ff00");
   cutg->SetLineColor(ci);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,20000,2000);
   cutg->SetPoint(1,20000,0);
   cutg->SetPoint(2,8611.33,0);
   cutg->SetPoint(3,6902.34,0);
   cutg->SetPoint(4,4897.14,0);
   cutg->SetPoint(5,-1000.05,0);
   cutg->SetPoint(6,-1027.34,2000);
   cutg->SetPoint(7,20000,2000);
   cutg->Draw("");
}
