#include <fcntl.h> //_O_U16TEXT
#include <io.h>    //_setmode()
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_LEN 1024

struct SINHVIEN {
	wchar_t MSSV[10];
	wchar_t HoTen[30];
	wchar_t Khoa[30];
	int Khoas;
	wchar_t Email[40];
	wchar_t NgaySinh[20];
	wchar_t HinhAnh[30];
	wchar_t MoTaBanThan[1000];
	wchar_t Sothich[1000];
};

void Docso(FILE*InFile, int& n)
{
	wchar_t c = fgetwc(InFile);
	if (c == '"')
	{
		fwscanf_s(InFile, L"%d", &n);
		fseek(InFile, 2L, SEEK_CUR);
	}
	else
	{
		fseek(InFile, -1L, SEEK_CUR);
		fwscanf_s(InFile, L"%d", &n);
		fseek(InFile, 1L, SEEK_CUR);
	}
}

void Docthongtin(FILE*fin, wchar_t a[MAX_STR_LEN])
{
	wchar_t ch = fgetwc(fin);
	int i = 0;
	while (1)
	{
		if (ch == ',' || ch == EOF || ch == '\n')
			break;
		a[i] = ch;
		i++;
		ch = fgetwc(fin);
	}
	a[i] = '\0';
}

void DocSothich(FILE*fin, wchar_t a[MAX_STR_LEN])
{
	wchar_t ch = fgetwc(fin);
	int i = 0;
	if (ch == '"')
	{
		while (1)
		{
			ch = fgetwc(fin);
			if (ch == '"' || ch == EOF || ch == '\n')
			{
				break;
			}
			a[i] = ch;
			i++;
		}
	}
	a[i] = '\0';
}

void Docsinhvien(FILE*fin, SINHVIEN &Viet)
{
		Docthongtin(fin, Viet.MSSV);
		Docthongtin(fin, Viet.HoTen);
		Docthongtin(fin, Viet.Khoa);
		Docso(fin, Viet.Khoas);
		Docthongtin(fin, Viet.Email);
		Docthongtin(fin, Viet.NgaySinh);
		Docthongtin(fin, Viet.HinhAnh);
		Docthongtin(fin, Viet.MoTaBanThan);
		Docthongtin(fin, Viet.Sothich);
}

int Demsinhvien(FILE*fin)
{
	wchar_t chr[1024];
	int count = 0;
	while (feof(fin) == NULL)
	{
		fgetws(chr, 1024, fin);
		count++;
	}
	return count - 1;
}

SINHVIEN* Docdanhsachsinhvien(FILE* fin, int &n)
{
	n = Demsinhvien(fin);
	fseek(fin, 0, 0);
	SINHVIEN* sv = (SINHVIEN*)malloc(n * sizeof(SINHVIEN));
	for (int i = 0; i < n; i++)
	{
		Docsinhvien(fin, sv[i]);
	}
	fclose(fin);
	return  sv;
}

void WritetoHTML(FILE*outFile, SINHVIEN sv)
{
	fwprintf(outFile, L"<!DOCTYPE html PUBLIC \" -//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\n");
	fwprintf(outFile, L"<html xmlns=\"http://www.w3.org/1999/xhtml\">\n");
	fwprintf(outFile, L"    <head>\n");
	fwprintf(outFile, L"        <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\n");
	fwprintf(outFile, L"        <link rel=\"stylesheet\" type=\"text/css\" href=\"personal.css\" />\n");
	fwprintf(outFile, L"        <title>HCMUS - %s</title>\n", sv.HoTen);
	fwprintf(outFile, L"    </head>\n");
	fwprintf(outFile, L"    <body>\n");
	fwprintf(outFile, L"        <div class=\"Layout_container\">\n");
	fwprintf(outFile, L"            <!-- Begin Layout Banner Region -->\n");
	fwprintf(outFile, L"            <div class=\"Layout_Banner\" >\n");
	fwprintf(outFile, L"                <div><img id=\"logo\" src=\"Images/logo.jpg\" height=\"105\" /></div>\n");
	fwprintf(outFile, L"                <div class=\"Header_Title\">TRƯỜNG ĐẠI HỌC KHOA HỌC TỰ NHIÊN </div>\n");
	fwprintf(outFile, L"            </div>\n");
	fwprintf(outFile, L"            <!-- End Layout Banner Region -->\n");
	fwprintf(outFile, L"            <!-- Begin Layout MainContents Region -->\n");
	fwprintf(outFile, L"                <div class=\"Layout_MainContents\">\n");
	fwprintf(outFile, L"                <!-- Begin Below Banner Region -->\n");
	fwprintf(outFile, L"                <div class=\"Personal_Main_Information\">\n");
	fwprintf(outFile, L"                    <!-- Begin Thông tin cá nhân c?a th?y cô ----------------------------------------------------------------------------------------- -->\n");
	fwprintf(outFile, L"                    <div class = \"Personal_Location\">\n");
	fwprintf(outFile, L"                        <img src=\"Images/LogoFooter.jpg\" width=\"27\" height=\"33\" />\n");
	fwprintf(outFile, L"                        <span class=\"Personal_FullName\">%s - %s</span>\n", sv.HoTen, sv.MSSV);
	fwprintf(outFile, L"                        <div class=\"Personal_Department\">KHOA CÔNG NGHỆ THÔNG TIN</div>\n");
	fwprintf(outFile, L"                        <br />\n");
	fwprintf(outFile, L"                        <div class=\"Personal_Phone\">\n");
	fwprintf(outFile, L"                             Email: %s\n", sv.Email);
	fwprintf(outFile, L"                        </div>\n");
	fwprintf(outFile, L"                        <br />\n");
	fwprintf(outFile, L"                        <br />\n");
	fwprintf(outFile, L"                    </div>\n");
	fwprintf(outFile, L"                    <!-- End Thông tin cá nhân c?a th?y cô ----------------------------------------------------------------------------------------- -->\n");
	fwprintf(outFile, L"                    <div class=\"Personal_HinhcanhanKhung\">\n");
	fwprintf(outFile, L"                        <img class=\"Personal_Hinhcanhan\" src=\"Images/%s.jpg\" />\n", sv.HinhAnh);
	fwprintf(outFile, L"                    </div>\n");
	fwprintf(outFile, L"                </div>\n");
	fwprintf(outFile, L"                <!-- End Below Banner Region -->\n");
	fwprintf(outFile, L"                <!-- Begin MainContents Region -->\n");
	fwprintf(outFile, L"                <div class=\"MainContain\">\n\n");
	fwprintf(outFile, L"                    <!-- Begin Top Region -->\n");
	fwprintf(outFile, L"                    <div class =\"MainContain_Top\">\n\n");
	fwprintf(outFile, L"                        <div class=\"InfoGroup\">Thông tin cá nhân</div>\n");
	fwprintf(outFile, L"                        <div>\n");
	fwprintf(outFile, L"                            <ul class=\"TextInList\">\n");
	fwprintf(outFile, L"                                <li>Họ và tên: %s</li>\n", sv.HoTen);
	fwprintf(outFile, L"                                <li>MSSV: %s</li>\n", sv.MSSV);
	fwprintf(outFile, L"                                <li>Sinh viên khoa Công nghệ thông tin</li>\n");
	fwprintf(outFile, L"                                <li>Ngày sinh: %s</li>\n", sv.NgaySinh);
	fwprintf(outFile, L"                                <li>Email: %s</li>\n", sv.Email);
	fwprintf(outFile, L"                            </ul>\n");
	fwprintf(outFile, L"                         </div>\n");
	fwprintf(outFile, L"                         <div class=\"InfoGroup\">Sở thích</div>\n");
	fwprintf(outFile, L"                         <div>\n");
	fwprintf(outFile, L"                            <ul class=\"TextInList\">\n");
	fwprintf(outFile, L"                               <li>Sở thích: %s</li>\n",sv.Sothich);
	fwprintf(outFile, L"                            </ul>\n");
	fwprintf(outFile, L"                        </div>\n");
	fwprintf(outFile, L"                        <div class=\"InfoGroup\">Mô tả</div>\n");
	fwprintf(outFile, L"                        <div class=\"Description\">\n");
	fwprintf(outFile, L"                            Tôi là một người %s\n", sv.MoTaBanThan);
	fwprintf(outFile, L"                        </div>\n\n");
	fwprintf(outFile, L"                    </div>\n");
	fwprintf(outFile, L"                </div>\n");
	fwprintf(outFile, L"            </div>\n\n");
	fwprintf(outFile, L"            <!-- Begin Layout Footer -->\n");
	fwprintf(outFile, L"            <div class=\"Layout_Footer\">\n");
	fwprintf(outFile, L"                <div class=\"divCopyright\">\n");
	fwprintf(outFile, L"                    <br />\n");
	fwprintf(outFile, L"                    <img src=\"Images/LogoFooter_gray.jpg\" width=\"34\" height=\"41\" />\n");
	fwprintf(outFile, L"                    <br />\n");
	fwprintf(outFile, L"                    <br />\n");
	fwprintf(outFile, L"                    @2013</br>\n");
	fwprintf(outFile, L"                    Đồ án giữa kỳ</br>\n");
	fwprintf(outFile, L"                Kỹ thuật lập trình</br>\n");
	fwprintf(outFile, L"                TH2012/03</br>\n");
	fwprintf(outFile, L"                1712904 - Nguyễn Bách Việt</br>\n");
	fwprintf(outFile, L"                </div>\n");
	fwprintf(outFile, L"            </div>\n");
	fwprintf(outFile, L"            <!-- End Layout Footer -->\n");
	fwprintf(outFile, L"        </div>\n");
	fwprintf(outFile, L"    </body>\n");
	fwprintf(outFile, L"</html>\n");
	fclose(outFile);
}

wint_t StrLen(wchar_t *c)
{
	wint_t count = 0;
	while (c[count] != L'\0')
	{
		count++;
	}
	return count;
}

wchar_t *TenFile(wchar_t *str)
{
	wint_t a = StrLen(str);
	wchar_t *str1 = new wchar_t[a + 5];

	for (wint_t i = 0; i < a ; i++)
	{
		str1[i] = str[i];
 	}
	str1[a] = L'.';
	str1[a + 1] = L'h';
	str1[a + 2] = L't';
	str1[a + 3] = L'm';
	str1[a + 4] = L'l';
	str1[a + 5] = L'\0';
	return str1;
}


void XuatFile(SINHVIEN *sv, int n)
{
	for (int i = 0; i < n; i++)
	{
		wchar_t *fname = TenFile(sv[i].MSSV);
		FILE* fout = _wfopen(fname, L"w, ccs=UTF-8");
		if (fout == NULL) 
		{
			wprintf(L"Không thể tạo file %s\n",fname);
		}
			WritetoHTML(fout, sv[i]);
	}
}

int wmain(int argc, wchar_t* argv[])
{
	
	_setmode(_fileno(stdout), _O_U16TEXT); //needed for output
	_setmode(_fileno(stdin), _O_U16TEXT); //needed for input

	wprintf(L"\t\tWEBSITE SINH VIÊN\n\n ");
	
	int n;
		// đọc file tiếng Việt
		FILE* fin = _wfopen(L"input.csv", L"r, ccs=UTF-8");
		if (!fin) {
			wprintf(L"Không thể đọc file userinfo-c.txt\n");
		}
		SINHVIEN* a = Docdanhsachsinhvien(fin,n);
		XuatFile(a, n);
		free(a);

	wprintf(L"Chương trình kết thúc.\n");
}
