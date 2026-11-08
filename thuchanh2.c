#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else       tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    static const int MAX_VEHICLES=3;
    phuong_tien pt[MAX_VEHICLES];
    int so_xe;
  

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    char lay_kich_thuoc() const;
    int lay_so_xe() const;
    bool day() const;
    bool them(const phuong_tien& v);
    bool xoa(int ma_xe);
    int tim_vi_tri(int ma_xe) const;
   
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), so_xe(0) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_xe(0) {}

int bai_xe::lay_ma() const { return ma_bai; }
bool bai_xe::day() const{
int suc_chua;
if(kich_thuoc =='S')
suc_chua=1;
else if(kich_thuoc=='M')
suc_chua=2;
else 
suc_chua=3;
return so_xe>=suc_chua;
}
int bai_xe::tim_vi_tri(int ma_xe) const{
	for(int i=0;i<so_xe;i++){
		if(pt[i].lay_ma_xe()==ma_xe)
		return i;
	}
	return -1;
}
 
bool bai_xe::them(const phuong_tien& v) {
    if(day())
    return false;
    if(tim_vi_tri(v.lay_ma_xe()) != -1)
    return false;
    if(so_xe>=MAX_VEHICLES)
    return false;
    pt[so_xe]=v;
    so_xe++;
    return true;
}

bool bai_xe::xoa(int ma_xe) {
	int vt=tim_vi_tri(ma_xe);
	if(vt==-1)
	return false;
	for(int i=vt;i<so_xe-1;i++){
		pt[i]=pt[i+1];
	}
	so_xe --;
	return true;
}
    

void bai_xe::hien_thi() const {
	int suc_chua;
    if(kich_thuoc =='S')
suc_chua=1;
else if(kich_thuoc=='M')
suc_chua=2;
else 
suc_chua=3;
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_xe << "/" << suc_chua << " xe\n";
         for(int i=0;i<so_xe;i++){
         	pt[i].hien_thi();
		 }
    
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
   
    for(int i=0;i<so_xe;i++){
    	if(pt[i].lay_loai_xe()==loai){
    		dem++;
    		tong +=pt[i].tinh_phi();
		}
	}
    return dem > 0;
}

class SystemInterface {
private:
	static const int MAX_LOTS =10;
	bai_xe bai[MAX_LOTS];
	int so_bai;
  

public:
    SystemInterface();
    bool co_ma_bai(int ma) const;
    bool co_ma_xe(int ma) const;
    void runMenu();
};


SystemInterface::SystemInterface() : so_bai(0){}
bool SystemInterface:: co_ma_bai(int ma) const{
	for(int i=0;i<so_bai;i++){
		if(bai[i].lay_ma()==ma)
		return true;
	}
	return false;
}
bool SystemInterface:: co_ma_xe(int ma) const{
	for(int i=0;i<so_bai;i++){
		if(bai[i].tim_vi_tri(ma) != -1)
		return true;
	}
	return false;
}
void SystemInterface::runMenu() {
    int chon;
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";
        cin >> chon;
    

        if (chon == 1) {
        	if(so_bai>=MAX_LOTS){
        		cout << "Da dat toi da 10 bai do!\n";
        		continue;
			}
            int ma; 
			char kt;
            cout << "Ma bai: ";
			cin >> ma;
			if(co_ma_bai(ma)){
				cout << "Ma bai da ton tai\n";
				continue;
			}
            cout << "Kich thuoc (S/M/L): "; cin >> kt;
            if(kt!='S'&&kt !='M'&&kt!='L'){
            	cout << "Kich thuoc khong hop le!\n";
            	continue;
			}
			bai[so_bai] = bai_xe(ma,kt);
			so_bai++;
            cout << "Da tao bai " << ma << "\n";
        }
        else if (chon == 2) {
        	if(so_bai ==0){
        		cout << "Chua co bai do nao\n";
        		continue;
        	
			}
            int ma_bai,ma, gio, tg; 
			string loai;
			cout << "Ma bai muon them xe: ";
			cin >> ma_bai;
			int vt_bai = -1;
			for(int i=0;i<so_bai;i++){
				if(bai[i].lay_ma()==ma_bai){
					vt_bai=i;
					break;
				}
			}
			if(vt_bai==-1){
					cout << "Khong tim thay bai do\n";
					continue;
				}
			if(bai[vt_bai].day()){
				cout << "Bai do da day\n";
				continue;
			}
            cout << "Ma xe: "; cin >> ma;
            if(co_ma_bai(ma)){
            	cout << "Ma xe da ton tai\n";
            	continue;
			}
            cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai;
            if(loai != "Car" && loai!="Bicycle"&&loai !="Motorcycle"){
            	cout << "Loai xe khong hop le!\n";
            	continue;
			}
            cout << "Gio vao (0-23): "; cin >> gio;
            cout << "Thoi luong (1-23): "; cin >> tg;
            phuong_tien v(ma, loai, gio, tg);
            if(bai[vt_bai].them(v)){
            	cout << "Da them xe" << ma << "| Phi: $"<<fixed<<setprecision(2)<<v.tinh_phi()<<"\n";
			}
			else{
				cout << "Khong the them xe\n";
			}
        }
        else if (chon == 3) {
            int ma;
            cout << "Ma bai can xoa: "; cin >> ma;
            int vt =-1;
            for(int i=0;i<so_bai;i++){
            	if(bai[i].lay_ma()==ma){
            		vt=i;
            		break;
				}
			}
			if(vt==-1){
				cout << "Khong tim thay bai do\n";
				continue;
			}
			for(int i=vt;i<so_bai-1;i++){
				bai[i]=bai[i+1];
			}
			so_bai--;
			cout<<"Da xoa bai"<<ma<<"\n";
    }
        
    
        else if (chon == 4) {
            int ma;
            cout << "Ma xe can lay ra: "; cin >> ma;
            bool ok = false;
            for(int i=0;i<so_bai;i++){
            	if(bai[i].xoa(ma)){
            		ok=true;
            		break;
				}
			}
            if(ok)
            cout << "Da lay xe ra!\n";
            else
            cout << "Khong tim thay xe!\n";
        }
        else if (chon == 5) {
        	if(so_bai==0){
        		cout<< "Chua co bai do nao\n";
			}
			for(int i=0;i<so_bai;i++){
				bai[i].hien_thi();
			}
            
        }
        else if (chon == 6) {
            int ma;
            cout << "Ma bai: "; cin >> ma;
            bool tim_thay=false;
            for(int i=0;i<so_bai;i++){
            	if(bai[i].lay_ma()==ma){
            		bai[i].hien_thi();
            		tim_thay=true;
            		break;
				}
			}
			if(!tim_thay)
			cout << "Khong tim thay bai do\n";
        }
        else if (chon == 7) {
            string loai;
            cout << "Loai xe: "; cin >> loai;
            if(loai != "Car" && loai!="Bicycle"&&loai !="Motorcycle"){
            	cout << "Loai xe  khong hop le!\n";
            	continue;
            }
            bool tim_thay=false;
            for(int i=0;i<so_bai;i++){
			
            int dem; double tong;
            if(bai[i].co_loai(loai,dem,tong)){
            	cout << "\nBai " << bai[i].lay_ma() << ":\n";
            	bai[i].hien_thi();
            	tim_thay=true;
			}
		}
		if(!tim_thay)
		cout << "Khong co xe thuoc loai nay\n";
        }
        else if (chon == 8) {
            string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
            for (int t = 0; t < 3; ++t) {
                int dem = 0; double tong = 0;
                for(int i=0;i<so_bai;i++){
                	int d;
                	double s;
                	bai[i].co_loai(loai_arr[t],d,s);
                	dem += d;
                	tong += s;
				}
				cout << loai_arr[t]<<": ";
				if(dem ==0){
					cout << "Khong co xe\n";
				}
				else {
					cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
            
				}
                
            }
        }
        else if (chon == 9) break;
    }
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
