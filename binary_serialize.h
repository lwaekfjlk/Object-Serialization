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

	/*�ҵ�˼·��
���ǽ��������struct��Ϊһ�࣬��Ϊ��Щ����ʹ��sizeof��ȡ�ʼ��������ݵ�size
��string��Ϊһ�࣬��Ϊ��������sizeof����ô�С��������Ȼ�����ٷ�
���ǽ������ࡢstruct��string��Ϊһ���࣬��Щ������Ϊʣ��stl�����Ļ���Ԫ��
��ʣ�µ�stl���Ϊһ���࣬������Ҫ���ϵ��ú���ֱ��������һ���࣬�������л��ͷ����л�
�ҵĺ���˼���ǣ������룬ֱ��������һ����Ԫ�أ��������л����ٻص���һ�㣬�����һ������񣬷�������һ�㣬ֱ��ȫ����ɣ�
���л���˳��Ҳ���ǳ��ֵ�˳������ļ��е�˳����һ�µ�
*/

//���ڲ��ԵĽṹ��



	/*deserialize��serialize�������Ƿ�װ�õĸ����û��Ľṹ����Ҫ������
�����������struck��������һ��templateģ���У���string�ࡢlist�ࡢvector�ࡢset�ࡢpair�ࡢmap�࣬���к���ʵ��Ƕ�׹���*/
/*serialize_sepecial��deserialize_special��Ҫ�Ǹ������û��ӿڵĺ�����������ʵ�ֹ��ܣ�����ʵ��Ƕ�׹���*/
/*main����ʵ�ֲ��Թ���*/
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





	//�����������struct����˺������������л�
	template <class T>
	void serialize(T &t, std::string file)
	{
		std::ofstream file_stream(file, std::ios::binary);
		serialize_special(t, file_stream);
		file_stream.close();
	}

	//�����������struct����˺��������з����л�
	template <class T>
	void deserialize(T &t, std::string file)
	{
		std::ifstream file_stream(file, std::ios::binary);
		deserialize_special(t, file_stream);
		file_stream.close();
	}

	//string�����˺������������л�
	void serialize(std::string &s, std::string file)
	{
		std::ofstream file_stream(file, std::ios::binary);
		serialize_special(s, file_stream);
		file_stream.close();
	}

	//string�����˺��������з����л�
	void deserialize(std::string &s, std::string file)
	{
		std::ifstream file_stream(file, std::ios::binary);
		deserialize_special(s, file_stream);
		file_stream.close();
	}



	//pair�����˺������������л���֮�����T�����ͽ��벻ͬ��special������������Ƕ��
	template<class T1, class T2>
	void serialize(std::pair < T1, T2 > &data, std::string file)
	{
		std::ofstream file_stream(file, std::ios::binary);

		//�ֱ��first��second���л�
		serialize_special(data.first, file_stream);
		serialize_special(data.second, file_stream);

		file_stream.close();
	}

	//pair�����˺��������з����л���֮�����T�����ͽ��벻ͬ��special������������Ƕ��
	template<class T1, class T2>
	void deserialize(std::pair<T1, T2> &data, std::string file)
	{
		std::ifstream file_stream(file, std::ios::binary);

		//�ֱ��first��second�����л�
		deserialize_special(data.first, file_stream);
		deserialize_special(data.second, file_stream);

		file_stream.close();
	}

	//vector�����˺������������л���֮�����T�����ͽ��벻ͬ��special������������Ƕ��
	template<class T>
	void serialize(std::vector < T > &data, std::string file)
	{
		std::ofstream file_stream(file, std::ios::binary);

		typename std::vector < T >::iterator i;

		//���ȵõ�size���浽����ļ����ǰ4���ֽ��У���int�ͣ����Ա㷴���л���ʹ��ʹ��
		int size = data.size();
		file_stream.write((char *)&size, 4);//��������ļ����ǰ4���ֽ�
		for (i = data.begin(); i != data.end(); i++)
		{
			serialize_special(*i, file_stream);//������л�
		}

		file_stream.close();
	}

	//vector�����˺��������з����л���֮�����T�����ͽ��벻ͬ��special������������Ƕ��
	template<class T>
	void deserialize(std::vector<T> &data, std::string file)
	{
		std::ifstream file_stream(file, std::ios::binary);

		int size;
		//�����л���˳���෴���Ȼ��size
		file_stream.read((char *)&size, 4);

		//�١����ݡ�
		data.resize(size);

		file_stream.seekg(4, std::ios::beg);
		typename std::vector <T >::iterator i;
		for (i = data.begin(); i != data.end(); i++)
		{
			deserialize_special(*i, file_stream);//��������л�
		}

		file_stream.close();
	}

	//list�����˺������������л���֮�����T�����ͽ��벻ͬ��special������������Ƕ��
	//list��set�������vector�Ǽ������Ƶģ�����׸��
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

	//list�����˺��������з����л���֮�����T�����ͽ��벻ͬ��special������������Ƕ��
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


	//set��map��ǰ�治һ�����ǣ�������stlû��resize���ֺ��������Բ�����֮ǰһ��ֱ�ӷ��룬��Ҫ�����Ȼ�����ݷ���ͬ�����͵�ret�У��ٲ�������
	//set�����˺������������л���֮�����T�����ͽ��벻ͬ��special������������Ƕ��
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

	//set�����˺��������з����л���֮�����T�����ͽ��벻ͬ��special������������Ƕ��
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

	//map�����˺������������л���֮�����T�����ͽ��벻ͬ��special������������Ƕ��
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

	//map�����˺��������з����л���֮�����T�����ͽ��벻ͬ��special������������Ƕ��
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




	//�������й�����ָ��ĺ���
	template <class T>
	void serialize(std::shared_ptr<T> & t, std::string file)
	{
		//��������Ϊһ�����л��������л�
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
		//���������л��������л�
		std::ofstream file_stream(file, std::ios::binary);
		serialize_special(*t, file_stream);
		file_stream.close();
	}

	template <class T>
	void deserialize(std::unique_ptr<T> & t, std::string file)
	{
		//�����ݷ����л���RetT�в���������ָ��ָ�������
		std::ifstream file_stream(file, std::ios::binary);
		T RetT;
		deserialize_special(RetT, file_stream);

		(*t) = RetT;

		file_stream.close();


	}




















	//ע�⣬��������XXX_special�ĺ������붼���ļ��������ã���ı�����λ�ã����������д�룬���Ḳ��


	//�ﵽ��ײ㣬��ʱ��Ϊ�������������struct�࣬�������л�
	template<class T>
	void serialize_special(T&t, std::ofstream &file_stream)
	{
		char ByteArray[10000];

		//���Ȼ���������������struct��ʱ��size���������ļ�ǰ4���ֽ���
		int ret = sizeof(t);
		file_stream.write((char *)&ret, 4);
		//���ڴ��е����ݷ���ByteArray������
		memcpy(ByteArray, &t, sizeof(t));
		//����������ݷ����ļ���
		file_stream.write(ByteArray, sizeof(t));
	}

	//�ﵽ��ײ㣬��ʱ��Ϊ�������������struct�࣬���з����л�
	template<class T>
	void deserialize_special(T&t, std::ifstream &file_stream)
	{
		char ByteArray[10000];
		int ret;
		//���Ȼ���������������struct��ʱ��size���������ļ�ǰ4���ֽ���
		file_stream.read((char *)&ret, 4);
		//���ļ��е����ݷŻ�������
		file_stream.read(ByteArray, ret);
		//mallocһ��T���͵�size���������
		T* RetT = (T*)malloc(ret);
		//�������е����ݷ��ڸ��½��ı�����
		memcpy(RetT, ByteArray, ret);
		//��ֵ��t
		t = *RetT;
		//�ͷŵ�
		free(RetT);
	}

	//�ﵽ��ײ㣬��ʱ��Ϊstring�࣬�������л�
	void serialize_special(std::string &s, std::ofstream &file_stream)
	{
		char ByteArray[10000];
		//��ó��ȣ���\0��
		int length = s.length();
		//�����ļ�
		file_stream.write((char *)&length, 4);
		//д������
		memcpy(ByteArray, s.c_str(), length);
		file_stream.write(ByteArray, length);
	}

	//�ﵽ��ײ㣬��ʱ��Ϊstring�࣬���з����л�
	void deserialize_special(std::string &data, std::ifstream &file_stream)
	{
		//�����л����������У�ע��ʹ��append����Ҫֱ�ӷ���c_str��
		char ByteArray[10000];
		int length;
		file_stream.read((char *)&length, 4);
		file_stream.read(ByteArray, length);
		data.append(ByteArray, length);
	}



	//pair�࣬������ײ㣬������T1��T2�ֱ����л�
	template<class T1, class T2>
	void serialize_special(std::pair<T1, T2> &data, std::ofstream &file_stream)
	{
		//ǰ����һ��
		serialize_special(data.first, file_stream);
		serialize_special(data.second, file_stream);

	}

	//pair�࣬������ײ㣬������T1��T2�ֱ����л�
	template<class T1, class T2>
	void deserialize_special(std::pair<T1, T2> &data, std::ifstream &file_stream)
	{
		//ǰ����һ��
		deserialize_special(data.first, file_stream);
		deserialize_special(data.second, file_stream);
	}


	//vector�࣬������ײ㣬������T���л�
	template<class T>
	void serialize_special(std::vector<T> &data, std::ofstream &file_stream)
	{
		//ǰ����һ��
		typename std::vector<T>::iterator i;

		//���size������ǰ4���ֽ�
		int size = data.size();
		file_stream.write((char *)&size, 4);
		for (i = data.begin(); i != data.end(); i++)
		{
			serialize_special(*i, file_stream);
		}

	}

	//vector�࣬������ײ㣬������T�����л�
	template<class T>
	void deserialize_special(std::vector<T> &data, std::ifstream &file_stream)
	{
		//ǰ����һ��
		typename std::vector<T>::iterator i;

		int size;

		file_stream.read((char *)&size, 4);
		data.resize(size);

		for (i = data.begin(); i != data.end(); i++)
		{
			deserialize_special(*i, file_stream);
		}


	}

	//list�࣬������ײ㣬������T���л�
	template<class T>
	void serialize_special(std::list<T> &data, std::ofstream &file_stream)
	{
		//ǰ����һ��
		typename std::list<T>::iterator i;

		int size = data.size();
		file_stream.write((char *)&size, 4);
		for (i = data.begin(); i != data.end(); i++)
		{
			serialize_special(*i, file_stream);
		}

	}

	//list�࣬������ײ㣬������T�����л�
	template<class T>
	void deserialize_special(std::list<T> &data, std::ifstream &file_stream)
	{
		//ǰ����һ��
		typename std::list<T>::iterator i;

		int size;

		file_stream.read((char *)&size, 4);
		data.resize(size);

		for (i = data.begin(); i != data.end(); i++)
		{
			deserialize_special(*i, file_stream);
		}
	}

	//set�࣬������ײ㣬������T���л�
	template<class T>
	void serialize_special(std::set<T> &data, std::ofstream &file_stream)
	{
		//ǰ����һ��
		typename std::set<T>::iterator i;

		int size = data.size();
		file_stream.write((char *)&size, 4);
		for (i = data.begin(); i != data.end(); i++)
		{
			serialize_special(*i, file_stream);
		}

	}

	//set�࣬������ײ㣬������T�����л�
	template<class T>
	void deserialize_special(std::set<T> &data, std::ifstream &file_stream)
	{
		//ǰ����һ��
		int size;

		file_stream.read((char *)&size, 4);

		T ret;
		for (int i = 0; i < size; i++)
		{
			deserialize_special(ret, file_stream);
			data.insert(ret);
		}
	}

	//map�࣬������ײ㣬������T���л�
	template<class T1, class T2>
	void serialize_special(std::map<T1, T2> &data, std::ofstream &file_stream)
	{
		//ǰ����һ��
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

	//map�࣬������ײ㣬������T�����л�
	template<class T1, class T2>
	void deserialize_special(std::map<T1, T2> &data, std::ifstream &file_stream)
	{
		//ǰ����һ��
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

