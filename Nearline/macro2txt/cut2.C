{
//========= Macro generated from object: cID_Z_AoQ0/
//========= by ROOT version6.16/00
   
   TCutG *cutg = new TCutG("cID_Z_AoQ0",9);
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
   cutg->SetPoint(0,2.64809,75.9024);
   cutg->SetPoint(1,2.63656,72.8944);
   cutg->SetPoint(2,2.58876,66.157);
   cutg->SetPoint(3,2.45013,69.6331);
   cutg->SetPoint(4,2.56571,76.8717);
   cutg->SetPoint(5,2.60031,76.4706);
   cutg->SetPoint(6,2.66786,76.3369);
   cutg->SetPoint(7,2.64809,75.9024);
   cutg->SetPoint(8,2.64809,75.9024);
   cutg->Draw("");
}
