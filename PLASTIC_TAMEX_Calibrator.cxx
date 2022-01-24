#include "PLASTIC_TAMEX_Calibrator.h"

using namespace std;

//---------------------------------------------------------------

PLASTIC_TAMEX_Calibrator::PLASTIC_TAMEX_Calibrator(bool ONLINE){

    this->ONLINE = ONLINE;


    nbins = 600;
    min_val = 0;
    max_val = 600;

    //only for ONLINE CALIBRATION
    if(this->ONLINE){
        fired = new bool*[100];
        for(int i = 0;i < 100;++i){
            fired[i] = new bool[100];
            for(int j = 0;j < 100;++j) fired[i][j] = false;
        }

        char tmp_name[1000];

        Fine_Hist = new TH1D**[100];
        for(int i = 0;i < 100;++i){
            Fine_Hist[i] = new TH1D*[100];
            for(int j = 0;j < 100;++j){
                sprintf(tmp_name,"PDF_%d_%d",i,j);
                Fine_Hist[i][j] = new TH1D(tmp_name,tmp_name,nbins,min_val,max_val);
            }
        }
    }
    else{
        bins_x_arr = new double[nbins];
        Cal_arr = new double**[100];
        for(int i = 0;i < 100;++i){
            Cal_arr[i] = new double*[100];
            for(int j = 0;j < 100;++j) Cal_arr[i][j] = new double[nbins];
        }
        fired = NULL;
        Fine_Hist = NULL;
        load_Calibration_Files();
    }
}

//---------------------------------------------------------------

PLASTIC_TAMEX_Calibrator::~PLASTIC_TAMEX_Calibrator(){
    if(ONLINE){
        for(int i = 0;i < 100;++i){
            for(int j = 0;j < 100;++j) delete Fine_Hist[i][j];
            delete[] fired[i];
            delete[] Fine_Hist[i];
        }
        delete[] Fine_Hist;
        delete[] fired;
    }
    else{
        for(int i = 0;i < 100;++i){
            for(int j = 0;j < 100;++j) if(Cal_arr[i][j]) delete[] Cal_arr[i][j];
            delete[] Cal_arr[i];
            delete[] wired_tamex_ch[i];
        }
        delete[] wired_tamex_ch;
        delete[] Cal_arr;
        delete[] bins_x_arr;
    }
}

//---------------------------------------------------------------
//This only happens when calibrator off
void PLASTIC_TAMEX_Calibrator::load_Calibration_Files(){
   
    //load calibration map for used ids
    ifstream map_file("Configuration_Files/bPlast/Calibration_PLASTIC_TAMEX/MAP.dat");

    string line;
    
    if(map_file.fail()){
        cerr << "Could not find PLASTIC_TAMEX Calibration file MAP" << endl;
        exit(0);
    }
  
    const char* format_MAP = "%d %d";

    int tamex_id,ch_id;
   // int ch_num[100][100];
    int used_ids[1000][100];
    iter = 0;

    wired_tamex_ch = new bool*[100];
    for(int i = 0;i < 100;++i){
        wired_tamex_ch[i] = new bool[100];
        for(int j = 0;j < 100;++j) wired_tamex_ch[i][j] = false;
    }

    while(map_file.good()){
        getline(map_file,line,'\n');
        if(line[0] == '#') continue;
        sscanf(line.c_str(),format_MAP,&tamex_id,&ch_id);
        used_ids[iter][0] = tamex_id;
        used_ids[iter][1] = ch_id;

        //cout << "used_ids[iter][0] "<<used_ids[iter][0] << " used_ids[iter][1] " << used_ids[iter][1]  << endl;

        wired_tamex_ch[tamex_id][ch_id] = true;

        iter++;
        
    }
    
    //Load all wired Calibration files specified by MAP
    char filename[1000];
    ifstream file;

    int b_iter = 0;
    double bin,val;

    //Cal_arr = new double**[10];

    const char* format = "%lf %lf";

    bool first = true;

    for(int i = 0;i < iter;++i){

        tamex_id = used_ids[i][0];
        ch_id = used_ids[i][1];
      
        //cout << tamex_id << " " << ch_id << endl;
        //Cal_arr[tamex_id] = new double*[100];

        b_iter = 0;

        //Cal_arr[tamex_id][ch_id] = new double[nbins];

        sprintf(filename,"Configuration_Files/bPlast/Calibration_PLASTIC_TAMEX/Calib_%d_%d.dat",tamex_id,ch_id);
        file.open(filename);

        if(file.fail()){
            cerr << "Could not find PLASTIC_TAMEX Calibration file " << tamex_id << " " << ch_id << endl;
            exit(0);
        }
        while(file.good()){
            getline(file,line,'\n');
            if(line[0] == '#') continue;
            sscanf(line.c_str(),format,&bin,&val);
            if(first) bins_x_arr[b_iter] = bin;
            Cal_arr[tamex_id][ch_id][b_iter] = val;
            b_iter++;
        }

        first = false;

        file.close();
        file.clear();
    }

}

//---------------------------------------------------------------

double PLASTIC_TAMEX_Calibrator::get_Calibration_val(double value,int tamex_id_tmp,int ch_id_tmp){
    
    double return_val = 0;
    double value_t = (double) value;
    double tmp,tmp2;

    for(int i = 0;i < nbins-1;++i){
//if(ch_id_tmp=-1) break;
     if(ch_id_tmp>-1&&ch_id_tmp<65){
        tmp = Cal_arr[tamex_id_tmp][ch_id_tmp][i];
    
        tmp2 = Cal_arr[tamex_id_tmp][ch_id_tmp][i+1];
        //cout << "calib "<<tmp << " " << tmp2 << " " << value << " " << bins_x_arr[i]<<endl;
        if(value >= bins_x_arr[i] && value < bins_x_arr[i+1]){
            
            return_val = (tmp2 - tmp)/(bins_x_arr[i+1] - bins_x_arr[i])*((value_t - bins_x_arr[i+1])+rand()%1000*0.001) + tmp;          
            break;
        }
     }
    }
    return return_val; //1000.; // Converts to ns
}

//---------------------------------------------------------------

void PLASTIC_TAMEX_Calibrator::get_data(double** fine_T,UInt** ch_id,int tamex_iter,int* iterator){
    //write into corresponding root histograms
    
    for(int i = 0;i < tamex_iter;++i){
        for(int j = 0;j < iterator[i];++j){
            if(i<9 && ch_id[i][j] <66){
           // if(ch_num[i][j]<32){
          // cout << "tamex_iter " << tamex_iter<< " i " << i << " iterator[i] "<< iterator[i]<< " j " << j <<" ch_id[i][j] " << ch_id[i][j] << endl; 
            Fine_Hist[i][ch_id[i][j]]->Fill(fine_T[i][j]);
            if(j %2 ==1) fired[i][ch_id[i][j]] = true;
            
           // }
           // cout<<"fired[i][ch_num[i][j]] " << fired[i][ch_num[i][j]] << " i " << i << " j " << j <<" ch_num[i][j] " << ch_num[i][j] << endl;}
            }
        }
    }
}

//---------------------------------------------------------------

void PLASTIC_TAMEX_Calibrator::ONLINE_CALIBRATION(){

    //Root file to check histograms
    //TFile* ROOT_FILE = new TFile("Root_Trees/PLASTIC_TAMEX_TREE.root","RECREATE");

    //output file stream
    ofstream cal_file;

    //MAP of used TamexIds with Channels 
    ofstream map_file("Configuration_Files/bPlast/Calibration_PLASTIC_TAMEX/MAP.dat");
    map_file << "#PLASTIC_TAMEX Calibration map" << endl;
    map_file << "#Map of used Tamex ids and their channels (if stated, used = True)" << endl;
    map_file << "#" << endl;
    map_file << "#tamex ids (0 or 1)    vs Channel Num." << endl;
    map_file << "#" << endl;


    cout << "ONLINE CALIBRATION FOR PLASTIC_TAMEX INITIALIZED" << endl;
    
    
    char filename[1000];
    
    //create sum spectra
    double sum_arr[nbins];
    double full_sum = 0;
    cout << "Running... ";
    cout.flush();

    int max_bin = 0;

    //binning array
    double bins_x[nbins],val = 0;
    for(int i = 0;i < nbins;++i) bins_x[i] = (max_val - min_val)/((double) nbins)*(i+1);

    //loop over all tamex modules and their respective channels
    for(int i = 0;i < 100;++i){
        for(int j = 0;j < 100;++j){
            //only if channel fired
            if(fired[i][j]){
           
                //add pdf and cdf to root file
                //ROOT_FILE->Add(Fine_Hist[i][j]);
                //ROOT_FILE->Add(Fine_Hist[i][j]->GetCumulative());

                sprintf(filename,"Configuration_Files/bPlast/Calibration_PLASTIC_TAMEX/Calib_%d_%d.dat",i,j);
                cal_file.open(filename);

                if(cal_file.fail()){
                    cerr << "Could not open " << filename << endl;
                    exit(0);
                }

                //used channel written in MAP file
                map_file << i << "\t" << j << endl;

                //header of calibration file
                cal_file << "# Calibration file of tamex_id " << i << " @ channel " << j << endl;
                cal_file << "# fine_T bin\t\t Calibration value" << endl;

                //calculating cdf for "real" case
                sum_arr[0] = Fine_Hist[i][j]->GetBinContent(1);
               
                for(int k = 1;k < nbins;++k){
                    sum_arr[k] = Fine_Hist[i][j]->GetBinContent(k+1) + sum_arr[k-1];
                    if(Fine_Hist[i][j]->GetBinContent(k+1) > 0) max_bin = k;
                    
                }

                //normalize cdf to 1 and calculate fine[i] = cdf[i]/sum*5000*picoseconds
                //write everything into calibration file (name of file = filename)
                full_sum = sum_arr[nbins-1];
                
                double default_value = 0;
                
                for(int k = 0;k < nbins;++k){
                    if(val > 0) default_value = 1;
                    val = (k < max_bin) ? ((double)(sum_arr[k]/full_sum)/*5000.0*/) : default_value;//0;
                    //cout <<"val " <<  val << endl;
                    cal_file << bins_x[k] << "\t\t" << val << endl;
                }
                
                cal_file.close();
                cal_file.clear();
            }
        }
        cout << "\r";
        cout << "Running... " << i << " % \t\t\t\t";
        cout.flush();
    }
    cout << "\r";
    cout << "Running... DONE" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "-> Exiting program after calibration <-\n" << endl;
    cout << "-> run program again to use new calibration <-" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << endl;

    //ROOT_FILE->Write();
        
    map_file.close();

    //closing does not work!
    //ROOT_FILE->Close();
}
