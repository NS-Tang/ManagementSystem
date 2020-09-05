/**自己写的一些MFC中可用的类和函数.
* @file zrsMFC.h
* @author 张润生
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
		/**把用separator间隔的字符串分成arrayLength个子字符串.
		* 分隔符只在字符串中间，不在开头和末尾，例如[substring0][separator][substring1][separator][substring2]
		* @param separator [in] 分隔符
		* @param string [in] 要分割的字符串
		* @param substrings [out] 分割后的字符串组
		*/
		void DivideStringIntoSubstrings(_In_  CString separator, _In_ CString & string, _Out_ std::vector<CString>& substrings);

		/**把arrayLength个子字符串连成用separator间隔的字符串.
		* 分隔符只在字符串中间，不在开头和末尾，例如[substring0][separator][substring1][separator][substring2]，不添加换行符
		* @param separator [in] 分隔符
		* @param string [out] 连接后的字符串
		* @param substrings [in] 要连接的字符串组
		*/
		void ConcatenateSubstringsIntoString(_In_ CString separator, _Out_ CString & string, _In_ std::vector<CString>& substring);
		/**从文件对象获取账户信息.
		* @param file [in] 输入的文件对象
		* @param acount [out] 输出的账户信息map
		*/
		void GetAcount(_In_ CStdioFile & file, _Out_ std::map<CString,CString>& acount);
		/**取账户信息写入文件对象.
		* @param file [out] 输出的文件对象
		* @param acount [in] 输入的账户信息map
		*/
		void SetAcount(_Out_ CStdioFile & file, _In_ std::map<CString,CString>& acount);

		/**点击列标题排序.
		* 首先在资源中添加LVN_COLUMNCLICK消息*/
		class SortingOnLvnColumnclickList
		{
		private:
			CImageList m_ImageList;
			static int m_sort_column;
			static bool m_method;

		private:
			/**自己定义的排序函数.*/
			static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
		public:

			/**增加上下箭头的图标.
			* IDI_ICON1为下箭头，IDI_ICON2为上箭头
			* OnInitDialog中调用
			* @param list 要增加图标的List Control
			*/
			void AddIcon(CListCtrl& list);

			/**点击列标题排序.
			* OnLvnColumnclickList中调用
			* @param sort_column 取值pNMLV->iSubItem
			* @param list 要排序的List Control
			*/
			static void run(int sort_column, CListCtrl& list);
		};
	}
}
#endif /* ZRS_MFC */
