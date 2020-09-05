/**�Լ�д��һЩMFC�п��õ���ͺ���.
* @file zrsMFC.h
* @author ������
*/
#pragma once
#ifndef ZRS_MFC
#define ZRS_MFC
#include "stdafx.h"
#include <vector>
#include <map>
#include "afxdialogex.h"



namespace zrs
{
	namespace MFC
	{
		/**����separator������ַ����ֳ�arrayLength�����ַ���.
		* �ָ���ֻ���ַ����м䣬���ڿ�ͷ��ĩβ������[substring0][separator][substring1][separator][substring2]
		* @param separator [in] �ָ���
		* @param string [in] Ҫ�ָ���ַ���
		* @param substrings [out] �ָ����ַ�����
		*/
		void DivideStringIntoSubstrings(_In_  CString separator, _In_ CString & string, _Out_ std::vector<CString>& substrings);

		/**��arrayLength�����ַ���������separator������ַ���.
		* �ָ���ֻ���ַ����м䣬���ڿ�ͷ��ĩβ������[substring0][separator][substring1][separator][substring2]������ӻ��з�
		* @param separator [in] �ָ���
		* @param string [out] ���Ӻ���ַ���
		* @param substrings [in] Ҫ���ӵ��ַ�����
		*/
		void ConcatenateSubstringsIntoString(_In_ CString separator, _Out_ CString & string, _In_ std::vector<CString>& substring);
		/**���ļ������ȡ�˻���Ϣ.
		* @param file [in] ������ļ�����
		* @param acount [out] ������˻���Ϣmap
		*/
		void GetAcount(_In_ CStdioFile & file, _Out_ std::map<CString,CString>& acount);
		/**ȡ�˻���Ϣд���ļ�����.
		* @param file [out] ������ļ�����
		* @param acount [in] ������˻���Ϣmap
		*/
		void SetAcount(_Out_ CStdioFile & file, _In_ std::map<CString,CString>& acount);

		/**����б�������.
		* ��������Դ�����LVN_COLUMNCLICK��Ϣ*/
		class SortingOnLvnColumnclickList
		{
		private:
			CImageList m_ImageList;
			static int m_sort_column;
			static bool m_method;

		private:
			/**�Լ������������.*/
			static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
		public:

			/**�������¼�ͷ��ͼ��.
			* IDI_ICON1Ϊ�¼�ͷ��IDI_ICON2Ϊ�ϼ�ͷ
			* OnInitDialog�е���
			* @param list Ҫ����ͼ���List Control
			*/
			void AddIcon(CListCtrl& list);

			/**����б�������.
			* OnLvnColumnclickList�е���
			* @param sort_column ȡֵpNMLV->iSubItem
			* @param list Ҫ�����List Control
			*/
			static void run(int sort_column, CListCtrl& list);
		};
	}
}
#endif /* ZRS_MFC */
