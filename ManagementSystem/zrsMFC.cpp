
#include "stdafx.h"
#include <vector>
#include "afxdialogex.h"
#include "resource.h"
#include "zrsMFC.h"

namespace zrs
{
	namespace MFC
	{
		void DivideStringIntoSubstrings(_In_ CString separator, _In_ CString & string, _Out_ std::vector<CString>& substrings)
		{
			int location = -1;
			int preLocation = -1;
			while ((location = string.Find(separator, preLocation + 1)) != -1)
			{
				substrings.push_back(string.Mid(preLocation + 1, location - preLocation - 1));
				preLocation = location;
			}
			substrings.push_back(string.Right(string.GetLength() - preLocation - 1));
		}


		void ConcatenateSubstringsIntoString(_In_ CString separator, _Out_ CString & string, _In_ std::vector<CString>& substring)
		{
			auto iter = substring.begin();
			string = *iter + separator;
			iter++;
			for (; iter != substring.end() - 1; iter++)
			{
				string += *iter + separator;
			}
			string += (*iter);
		}

		void GetAcount(_In_ CStdioFile & file, _Out_ std::map<CString, CString>& acount)
		{
			// TODO: 在此处插入 return 语句
			CString string;
			while (file.ReadString(string))
			{
				std::vector<CString> unamePwd;
				zrs::MFC::DivideStringIntoSubstrings("\t", string, unamePwd);
				acount.insert(std::pair<CString, CString>(unamePwd[0], unamePwd[1]));
			}
		}

		void SetAcount(_Out_ CStdioFile & file, _In_ std::map<CString, CString>& acount)
		{
			for (auto iter = acount.begin(); iter != acount.end(); iter++)
			{
				file.WriteString(iter->first + "\t" + iter->second + "\n");
			}
		}



		//class SortingOnLvnColumnclickList:begin

		int SortingOnLvnColumnclickList::m_sort_column = -1;
		bool SortingOnLvnColumnclickList::m_method = false;

		int CALLBACK SortingOnLvnColumnclickList::MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
		{
			int row1 = (int)lParam1;
			int row2 = (int)lParam2;
			CListCtrl* lc = (CListCtrl*)lParamSort;
			CString lp1 = lc->GetItemText(row1, m_sort_column);
			CString lp2 = lc->GetItemText(row2, m_sort_column);
			LPCTSTR s1 = (LPCTSTR)lp1;
			LPCTSTR s2 = (LPCTSTR)lp2;
			if (m_method)
			{
				return  strcmp(s2, s1);
			}
			else
			{
				return  strcmp(s1, s2);
			}
		}


		void SortingOnLvnColumnclickList::AddIcon(CListCtrl& list)
		{
			CHeaderCtrl *pHeaderCtrl = list.GetHeaderCtrl();

			m_ImageList.Create(16, 16, ILC_COLOR16 | ILC_MASK, 0, 4);
			m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
			m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
			pHeaderCtrl->SetImageList(&m_ImageList);
		}


		void SortingOnLvnColumnclickList::run(int sort_column, CListCtrl& list)
		{
			int count = list.GetItemCount();

			for (int i = 0; i < count; i++)
			{
				list.SetItemData(i, i);
			}
			CHeaderCtrl* pHdrCtrl = list.GetHeaderCtrl();
			if (pHdrCtrl && pHdrCtrl->GetSafeHwnd())
			{
				int n = pHdrCtrl->GetItemCount();

				HDITEM hdi = { 0 };
				TCHAR szBuf[129] = { 0 };
				hdi.mask = HDI_TEXT;
				hdi.pszText = szBuf;
				hdi.cchTextMax = 128;

				for (int i = 0; i < n; i++)
				{
					hdi.mask = HDI_IMAGE | HDI_FORMAT;
					pHdrCtrl->GetItem(i, &hdi);
					if (i == sort_column)
					{
						if (hdi.fmt & HDF_IMAGE)
						{
							hdi.iImage = 1 - hdi.iImage;
							m_method = !m_method;
						}
						else
						{
							hdi.iImage = 0;
							hdi.fmt |= HDF_IMAGE | HDF_BITMAP_ON_RIGHT;
							if (m_method)
							{
								hdi.iImage = 1 - hdi.iImage;
							}
						}
					}
					else
					{
						hdi.mask = HDI_FORMAT;
						hdi.fmt &= ~HDF_IMAGE & ~HDF_BITMAP_ON_RIGHT;
					}

					pHdrCtrl->SetItem(i, &hdi);
				}
			}
			m_sort_column = sort_column;
			list.SortItems(MyCompareProc, (DWORD)&list);
		}
		//class SortingOnLvnColumnclickList:end
	}
}
