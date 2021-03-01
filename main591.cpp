//591. 标签验证器

#include <cstdio>
#include <vector>
#include <string>
#include <stack>

using namespace std;

bool isValid(string code) {
    //思路：需要闭合，使用栈

    stack<pair<int,int>> tags;
    int tagStart = -1;
    bool iscdata = false;
    for(int i=0;i<code.size();++i)
    {
        if(iscdata)
        {
            if(code[i] == ']' && i+2<code.size() && code[i+1] == ']' && code[i+2]=='>') //cdata结束
            {
                iscdata = false;
                i+=2;
                continue;
            }
        }
        else
        {
            if(code[i] == '<')
            {
                if(i+8 < code.size() && code.substr(i,9) == "<![CDATA[")
                {
                    iscdata = true;
                    i+=8;
                    continue;
                }
                else
                {
                        printf("get2:%d start:%d\n",i,tagStart);
                    if(tagStart == -1)
                    {
                        tagStart = i+1;
                    }
                    else
                    {
                        return false;   // < 必须匹配
                    }
                    
                }
                
            }
            else if(code[i] == '>')
            {
                if(tagStart > -1) //检测标签
                {
                    printf("ddd:%c start:%d\n",code[tagStart],tagStart);
                    if(i - tagStart < 1 || (i -tagStart > (code[tagStart]=='/' ? 10 : 9))) //长度控制
                    {
                        return false;
                    }
                    // int j = code[tagStart] == '/' ? tagStart+1 : tagStart;
                    for(int j=tagStart;j<i;++j)
                    {
                        if(!((code[j] >= 'A' && code[j] <= 'Z') || code[j] == '/'))
                        {
                            return false; //tag必须全部大写
                        }
                    }

                    if(code[tagStart] == '/')
                    {
                        if(tags.empty())
                        {
                            return false;
                        }

                        int preStart = tags.top().first;
                        int preEnd = tags.top().second;
                        for(int j=preStart;j<=preEnd;++j)
                        {
                            if(code[j] != code[tagStart+1+j-preStart])
                            {
                                return false;
                            }
                        }

                        tags.pop(); //匹配后弹出
                        if(tags.empty() && i!=code.size()-1)
                        {
                            return false;
                        }

                        if(i == code.size()-1)
                        {
                            return preStart == 1; //所有代码都要在闭合标签里
                        }
                    }
                    else
                    {
                        tags.push({tagStart,i-1});
                    }

                    tagStart = -1;
                    
                }
            }
        }
    }

    return false;
}

int main()
{
    string aa = "<DIV>This is the first line <![CDATA[<div>]]></DIV>"; //true
    aa = "<DIV>>>  ![cdata[]] <![CDATA[<div>]>]]>]]>>]</DIV>"; //true
    // aa = "<A>  <B> </A>   </B>"; //false
    // aa = "<DIV>  div tag is not closed  <DIV>";//false
    // aa = "<DIV>  unmatched <  </DIV>"; //false
    // aa = "<DIV> closed tags with invalid tag name  <b>123</b> </DIV>"; //false;
    // aa = "<DIV> unmatched tags with invalid tag name  </1234567890> and <CDATA[[]]>  </DIV>"; //false
    // aa = "<DIV>  unmatched start tag <B>  and unmatched end tag </C>  </DIV>";//false
    // aa = "<A></A><B></B>"; //false
    // aa = "<![CDATA[ABC]]><TAG>sometext</TAG>"; // false
    aa = "<DIV><YFSYYS><UVBNIQ><XPMXUNT><WNGMV><OJJGQREMT><Z><GEJDP><LIQS><NCVYU><RAS><UYFKCJCDN><NA><POJVYT><Z><TDC><VUIZQC><BNANGX><TOF><MR>MK</MR></TOF></BNANGX></VUIZQC></TDC></Z></POJVYT></NA></UYFKCJCDN></RAS></NCVYU></LIQS></GEJDP></Z></OJJGQREMT></WNGMV></XPMXUNT></UVBNIQ></YFSYYS></DIV>";//true
    aa = "<UYFKCJCDN><MR>MK</MR></UYFKCJCDN>";
    printf(isValid(aa) ? "true\n" : "false\n");

    return 0;
}