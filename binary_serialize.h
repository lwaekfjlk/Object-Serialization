#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <array>
#include <iostream>
#include <fstream>
#include <streambuf> 
#include<algorithm>

namespace binary_serialize
{

	/*我的思路：
我们将算术类和struct分为一类，因为这些可以使用sizeof获取最开始输入的数据的size
将string分为一类，因为它不能用sizeof来获得大小，但是依然不可再分
我们将算术类、struct和string分为一大类，这些可以作为剩下stl容器的基本元素
将剩下的stl类分为一大类，可能需要不断调用函数直到碰到第一大类，进行序列化和反序列化
我的核心思想是：逐层剥离，直到遇到第一大类元素，进行序列化，再回到上一层，完成上一层的任务，返回再上一层，直到全部完成；
序列化的顺序也就是出现的顺序和在文件中的顺序是一致的
*/

//用于测试的结构体



	/*deserialize和serialize函数都是封装好的给予用户的结构，主要包括：
基本算数类和struck（整合在一个template模板中）、string类、list类、vector类、set类、pair类、map类，其中后面实现嵌套功能*/
/*serialize_sepecial和deserialize_special主要是跟在与用户接口的函数下面真正实现功能，方便实现嵌套功能*/
/*main函数实现测试功能*/
	template <class T>
	void serialize(T &t, std::string file);
	template <class T>
	void deserialize(T &t, std::string file);
	void serialize(std::string &s, std::string file);
	void deserialize(std::string &s, std::string file);
	template<class T1, class T2>
	void serialize(std::pair < T1, T2 > &data, std::string file);
	template<class T1, class T2>
	void deserialize(std::pair < T1, T2 > &data, std::string file);
	template<class T>
	void serialize(std::vector<T> &data, std::string file);
	template<class T>
	void deserialize(std::vector<T> &data, std::string file);
	template<class T>
	void serialize(std::list<T> &data, std::string file);
	template<class T>
	void deserialize(std::list<T> &data, std::string file);
	template<class T>
	void serialize(std::set<T> &data, std::string file);
	template<class T>
	void deserialize(std::set<T> &data, std::string file);
	template<class T1, class T2>
	void serialize(std::map < T1, T2 > &data, std::string file);
	template<class T1, class T2>
	void deserialize(std::map < T1, T2 > &data, std::string file);


	template<class T>
	void serialize_special(T&t, std::ofstream &file_stream);
	template<class T>
	void deserialize_special(T&t, std::ifstream &file_stream);
	void serialize_special(std::string &s, std::ofstream &file_stream);
	void deserialize_special(std::string &data, std::ifstream &file_stream);
	template<class T>
	void deserialize_special(std::vector<T> &data, std::ifstream &file_stream);
	template<class T>
	void serialize_special(std::vector<T> &data, std::ofstream &file_stream);
	template<class T1, class T2>
	void serialize_special(std::pair<T1, T2> &data, std::ofstream &file_stream);
	template<class T1, class T2>
	void deserialize_special(std::pair<T1, T2> &data, std::ifstream &file_stream);
	template<class T>
	void serialize_special(std::list<T> &data, std::ofstream &file_stream);
	template<class T>
	void deserialize_special(std::list<T> &data, std::ifstream &file_stream);
	template<class T>
	void serialize_special(std::set<T> &data, std::ofstream &file_stream);
	template<class T>
	void deserialize_special(std::set<T> &data, std::ifstream &file_stream);
	template<class T1, class T2>
	void serialize_special(std::map<T1, T2> &data, std::ofstream &file_stream);
	template<class T1, class T2>
	void deserialize_special(std::map<T1, T2> &data, std::ifstream &file_stream);





	//算数基本类和struct进入此函数，进行序列化
	template <class T>
	void serialize(T &t, std::string file)
	{
		std::ofstream file_stream(file, std::ios::binary);
		serialize_special(t, file_stream);
		file_stream.close();
	}

	//算数基本类和struct进入此函数，进行反序列化
	template <class T>
	void deserialize(T &t, std::string file)
	{
		std::ifstream file_stream(file, std::ios::binary);
		deserialize_special(t, file_stream);
		file_stream.close();
	}

	//string类进入此函数，进行序列化
	void serialize(std::string &s, std::string file)
	{
		std::ofstream file_stream(file, std::ios::binary);
		serialize_special(s, file_stream);
		file_stream.close();
	}

	//string类进入此函数，进行反序列化
	void deserialize(std::string &s, std::string file)
	{
		std::ifstream file_stream(file, std::ios::binary);
		deserialize_special(s, file_stream);
		file_stream.close();
	}



	//pair类进入此函数，进行序列化，之后根据T的类型进入不同的special二级函数进行嵌套
	template<class T1, class T2>
	void serialize(std::pair < T1, T2 > &data, std::string file)
	{
		std::ofstream file_stream(file, std::ios::binary);

		//分别对first和second序列化
		serialize_special(data.first, file_stream);
		serialize_special(data.second, file_stream);

		file_stream.close();
	}

	//pair类进入此函数，进行反序列化，之后根据T的类型进入不同的special二级函数进行嵌套
	template<class T1, class T2>
	void deserialize(std::pair<T1, T2> &data, std::string file)
	{
		std::ifstream file_stream(file, std::ios::binary);

		//分别对first和second反序列化
		deserialize_special(data.first, file_stream);
		deserialize_special(data.second, file_stream);

		file_stream.close();
	}

	//vector类进入此函数，进行序列化，之后根据T的类型进入不同的special二级函数进行嵌套
	template<class T>
	void serialize(std::vector < T > &data, std::string file)
	{
		std::ofstream file_stream(file, std::ios::binary);

		typename std::vector < T >::iterator i;

		//首先得到size并存到这个文件块的前4个字节中（用int型），以便反序列化的使用使用
		int size = data.size();
		file_stream.write((char *)&size, 4);//放在这个文件块的前4个字节
		for (i = data.begin(); i != data.end(); i++)
		{
			serialize_special(*i, file_stream);//逐个序列化
		}

		file_stream.close();
	}

	//vector类进入此函数，进行反序列化，之后根据T的类型进入不同的special二级函数进行嵌套
	template<class T>
	void deserialize(std::vector<T> &data, std::string file)
	{
		std::ifstream file_stream(file, std::ios::binary);

		int size;
		//和序列化的顺序相反，先获得size
		file_stream.read((char *)&size, 4);

		//再“扩容”
		data.resize(size);

		file_stream.seekg(4, std::ios::beg);
		typename std::vector <T >::iterator i;
		for (i = data.begin(); i != data.end(); i++)
		{
			deserialize_special(*i, file_stream);//逐个反序列化
		}

		file_stream.close();
	}

	//list类进入此函数，进行序列化，之后根据T的类型进入不同的special二级函数进行嵌套
	//list、set和上面的vector是极其类似的，不再赘述
	template<class T>
	void serialize(std::list < T > &data, std::string file)
	{
		std::ofstream file_stream(file, std::ios::binary);

		typename std::list < T >::iterator i;

		int size = data.size();
		file_stream.write((char *)&size, 4);
		for (i = data.begin(); i != data.end(); i++)
		{
			serialize_special(*i, file_stream);
		}

		file_stream.close();
	}

	//list类进入此函数，进行反序列化，之后根据T的类型进入不同的special二级函数进行嵌套
	template<class T>
	void deserialize(std::list<T> &data, std::string file)
	{
		std::ifstream file_stream(file, std::ios::binary);

		int size;

		file_stream.read((char *)&size, 4);
		data.resize(size);

		file_stream.seekg(4, std::ios::beg);
		typename std::list <T >::iterator i;
		for (i = data.begin(); i != data.end(); i++)
		{
			deserialize_special(*i, file_stream);
		}

		file_stream.close();
	}


	//set、map和前面不一样的是，这两类stl没有resize这种函数，所以不能像之前一样直接放入，需要我们先获得内容放在同样类型的ret中，再插入其中
	//set类进入此函数，进行序列化，之后根据T的类型进入不同的special二级函数进行嵌套
	template<class T>
	void serialize(std::set < T > &data, std::string file)
	{
		std::ofstream file_stream(file, std::ios::binary);

		typename std::set < T >::iterator i;

		int size = data.size();
		file_stream.write((char *)&size, 4);
		for (i = data.begin(); i != data.end(); i++)
		{
			serialize_special(*i, file_stream);
		}

		file_stream.close();
	}

	//set类进入此函数，进行反序列化，之后根据T的类型进入不同的special二级函数进行嵌套
	template<class T>
	void deserialize(std::set<T> &data, std::string file)
	{
		std::ifstream file_stream(file, std::ios::binary);

		int size;

		file_stream.read((char *)&size, 4);

		file_stream.seekg(4, std::ios::beg);
		T ret;
		for (int i = 0; i < size; i++)
		{
			deserialize_special(ret, file_stream);
			data.insert(ret);
		}

		file_stream.close();
	}

	//map类进入此函数，进行序列化，之后根据T的类型进入不同的special二级函数进行嵌套
	template<class T1, class T2>
	void serialize(std::map < T1, T2 > &data, std::string file)
	{
		std::ofstream file_stream(file, std::ios::binary);
		typename std::map < T1, T2 >::iterator i;

		int size = data.size();
		file_stream.write((char *)&size, 4);
		for (i = data.begin(); i != data.end(); i++)
		{
			serialize_special(i->first, file_stream);
			serialize_special(i->second, file_stream);
		}

		file_stream.close();
	}

	//map类进入此函数，进行反序列化，之后根据T的类型进入不同的special二级函数进行嵌套
	template<class T1, class T2>
	void deserialize(std::map<T1, T2> &data, std::string file)
	{
		std::ifstream file_stream(file, std::ios::binary);

		int size;

		file_stream.read((char *)&size, 4);

		file_stream.seekg(4, std::ios::beg);
		T1 ret1;
		T2 ret2;
		for (int i = 0; i != size; i++)
		{
			deserialize_special(ret1, file_stream);
			deserialize_special(ret2, file_stream);
			data[ret1] = ret2;
		}

		file_stream.close();
	}




	//下面是有关智能指针的函数
	template <class T>
	void serialize(std::shared_ptr<T> & t, std::string file)
	{
		//将内容作为一个序列化并反序列化
		std::ofstream file_stream(file, std::ios::binary);
		serialize_special(*t, file_stream);
		file_stream.close();
	}

	template <class T>
	void deserialize(std::shared_ptr<T> & t, std::string file)
	{

		std::ifstream file_stream(file, std::ios::binary);

		T RetT;
		deserialize_special(RetT, file_stream);
		
		
		(*t) = RetT;

		file_stream.close();


	}



	template <class T>
	void serialize(std::unique_ptr<T> & t, std::string file)
	{
		//将内容序列化并反序列化
		std::ofstream file_stream(file, std::ios::binary);
		serialize_special(*t, file_stream);
		file_stream.close();
	}

	template <class T>
	void deserialize(std::unique_ptr<T> & t, std::string file)
	{
		//将内容反序列化到RetT中并放入智能指针指向的内容
		std::ifstream file_stream(file, std::ios::binary);
		T RetT;
		deserialize_special(RetT, file_stream);

		(*t) = RetT;

		file_stream.close();


	}




















	//注意，下面所有XXX_special的函数传入都是文件流的引用，会改变流的位置，所以是向后写入，不会覆盖


	//达到最底层，此时类为算数基本类或者struct类，进行序列化
	template<class T>
	void serialize_special(T&t, std::ofstream &file_stream)
	{
		char ByteArray[10000];

		//首先获得算数基本类或者struct此时的size，并放入文件前4个字节中
		int ret = sizeof(t);
		file_stream.write((char *)&ret, 4);
		//将内存中的内容放入ByteArray数组中
		memcpy(ByteArray, &t, sizeof(t));
		//将数组的内容放入文件中
		file_stream.write(ByteArray, sizeof(t));
	}

	//达到最底层，此时类为算数基本类或者struct类，进行反序列化
	template<class T>
	void deserialize_special(T&t, std::ifstream &file_stream)
	{
		char ByteArray[10000];
		int ret;
		//首先获得算数基本类或者struct此时的size，并放入文件前4个字节中
		file_stream.read((char *)&ret, 4);
		//将文件中的内容放回数组中
		file_stream.read(ByteArray, ret);
		//malloc一个T类型的size，以免溢出
		T* RetT = (T*)malloc(ret);
		//将数组中的内容放在刚新建的变量中
		memcpy(RetT, ByteArray, ret);
		//赋值给t
		t = *RetT;
		//释放掉
		free(RetT);
	}

	//达到最底层，此时类为string类，进行序列化
	void serialize_special(std::string &s, std::ofstream &file_stream)
	{
		char ByteArray[10000];
		//获得长度（含\0）
		int length = s.length();
		//放入文件
		file_stream.write((char *)&length, 4);
		//写入内容
		memcpy(ByteArray, s.c_str(), length);
		file_stream.write(ByteArray, length);
	}

	//达到最底层，此时类为string类，进行反序列化
	void deserialize_special(std::string &data, std::ifstream &file_stream)
	{
		//和序列化反过来就行，注意使用append，不要直接放在c_str中
		char ByteArray[10000];
		int length;
		file_stream.read((char *)&length, 4);
		file_stream.read(ByteArray, length);
		data.append(ByteArray, length);
	}



	//pair类，不是最底层，继续对T1和T2分别序列化
	template<class T1, class T2>
	void serialize_special(std::pair<T1, T2> &data, std::ofstream &file_stream)
	{
		//前往下一层
		serialize_special(data.first, file_stream);
		serialize_special(data.second, file_stream);

	}

	//pair类，不是最底层，继续对T1和T2分别反序列化
	template<class T1, class T2>
	void deserialize_special(std::pair<T1, T2> &data, std::ifstream &file_stream)
	{
		//前往下一层
		deserialize_special(data.first, file_stream);
		deserialize_special(data.second, file_stream);
	}


	//vector类，不是最底层，继续对T序列化
	template<class T>
	void serialize_special(std::vector<T> &data, std::ofstream &file_stream)
	{
		//前往下一层
		typename std::vector<T>::iterator i;

		//获得size并放入前4个字节
		int size = data.size();
		file_stream.write((char *)&size, 4);
		for (i = data.begin(); i != data.end(); i++)
		{
			serialize_special(*i, file_stream);
		}

	}

	//vector类，不是最底层，继续对T反序列化
	template<class T>
	void deserialize_special(std::vector<T> &data, std::ifstream &file_stream)
	{
		//前往下一层
		typename std::vector<T>::iterator i;

		int size;

		file_stream.read((char *)&size, 4);
		data.resize(size);

		for (i = data.begin(); i != data.end(); i++)
		{
			deserialize_special(*i, file_stream);
		}


	}

	//list类，不是最底层，继续对T序列化
	template<class T>
	void serialize_special(std::list<T> &data, std::ofstream &file_stream)
	{
		//前往下一层
		typename std::list<T>::iterator i;

		int size = data.size();
		file_stream.write((char *)&size, 4);
		for (i = data.begin(); i != data.end(); i++)
		{
			serialize_special(*i, file_stream);
		}

	}

	//list类，不是最底层，继续对T反序列化
	template<class T>
	void deserialize_special(std::list<T> &data, std::ifstream &file_stream)
	{
		//前往下一层
		typename std::list<T>::iterator i;

		int size;

		file_stream.read((char *)&size, 4);
		data.resize(size);

		for (i = data.begin(); i != data.end(); i++)
		{
			deserialize_special(*i, file_stream);
		}
	}

	//set类，不是最底层，继续对T序列化
	template<class T>
	void serialize_special(std::set<T> &data, std::ofstream &file_stream)
	{
		//前往下一层
		typename std::set<T>::iterator i;

		int size = data.size();
		file_stream.write((char *)&size, 4);
		for (i = data.begin(); i != data.end(); i++)
		{
			serialize_special(*i, file_stream);
		}

	}

	//set类，不是最底层，继续对T反序列化
	template<class T>
	void deserialize_special(std::set<T> &data, std::ifstream &file_stream)
	{
		//前往下一层
		int size;

		file_stream.read((char *)&size, 4);

		T ret;
		for (int i = 0; i < size; i++)
		{
			deserialize_special(ret, file_stream);
			data.insert(ret);
		}
	}

	//map类，不是最底层，继续对T序列化
	template<class T1, class T2>
	void serialize_special(std::map<T1, T2> &data, std::ofstream &file_stream)
	{
		//前往下一层
		int size = data.size();
		file_stream.write((char *)&size, 4);

		typename std::map<T1, T2>::iterator i;
		for (i = data.begin(); i != data.end(); i++)
		{
			T1 ret1 = i->first;
			T2 ret2 = i->second;
			serialize_special(ret1, file_stream);
			serialize_special(ret2, file_stream);
		}

	}

	//map类，不是最底层，继续对T反序列化
	template<class T1, class T2>
	void deserialize_special(std::map<T1, T2> &data, std::ifstream &file_stream)
	{
		//前往下一层
		typename std::map<T1, T2>::iterator i;
		int size;

		file_stream.read((char *)&size, 4);
		for (int i = 0; i < size; i++)
		{
			T1 ret1;
			T2 ret2;
			deserialize_special(ret1, file_stream);
			deserialize_special(ret2, file_stream);
			data[ret1] = ret2;
		}

	}

}


class Test
{
public:
	Test(std::string s)
	{
		str = s;
		std::cout << "Test creat\n";
	}
	~Test()
	{
		std::cout << "Test delete:" << str << std::endl;
	}
	std::string& getStr()
	{
		return str;
	}
	void setStr(std::string s)
	{
		str = s;
	}
	void print()
	{
		std::cout << str << std::endl;
	}
private:
	std::string str;
};

