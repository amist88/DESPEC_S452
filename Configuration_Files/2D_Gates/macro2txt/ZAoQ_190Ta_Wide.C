{
//========= Macro generated from object: cID_Z_AoQ0/
//========= by ROOT version6.18/04
   
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
   cutg->SetLineWidth(3);
   cutg->SetPoint(0,2.63943,73.4167);
   cutg->SetPoint(1,2.64598,73.2083);
   cutg->SetPoint(2,2.62996,72.6813);
   cutg->SetPoint(3,2.57889,72.6693);
   cutg->SetPoint(4,2.5783,73.3534);
   cutg->SetPoint(5,2.59069,73.4981);
   cutg->SetPoint(6,2.62177,73.4468);
   cutg->SetPoint(7,2.63943,73.4167);
   cutg->Draw("");
}
