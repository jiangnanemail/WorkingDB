#pragma once

/*
	定义公共基本原子元素
*/

/*
	二维元素
*/

template<typename U1, typename U2>
class TWPairObjAtom
{
public:
	TWPairObjAtom( IN const U1& Atom1, IN const U2& Atom2 )
	:m_Atom1(Atom1),m_Atom2(Atom2)                                                                 {};
	TWPairObjAtom()
	:m_Atom1(),m_Atom2()                                                                           {};
	virtual ~TWPairObjAtom()                                                                       {};

	//get or set function
	U1& GetAtom1()                                                                                 { return m_Atom1; };
	U1 GetAtom1() const                                                                            { return m_Atom1; };
	U2& GetAtom2()                                                                                 { return m_Atom2; };
	U2 GetAtom2() const                                                                            { return m_Atom2; };
	void SetAtom1( const U1& Item )                                                                { m_Atom1 = Item; };
	void SetAtom2( const U2& Item )                                                                { m_Atom2 = Item; };
private:
	U1            m_Atom1;
	U2            m_Atom2;
};


/*
	三维元素
*/

template<typename U1, typename U2, typename U3>
class TWTripleObjAtom :public TWPairObjAtom<U1, U2>
{
public:
	TWTripleObjAtom( IN const U1& Atom1, IN const U2& Atom2, IN const U3 Atom3 )
	:TWPairObjAtom( Atom1, Atom2 ), m_Atom3( Atom3 )                                               {}
	TWTripleObjAtom():TWPairObjAtom(), m_Atom3()                                                   {}
	virtual ~TWTripleObjAtom()                                                                     {}

	const TWTripleObjAtom& operator = ( IN const TWTripleObjAtom& Item )
	{
		if( this != &Item )
		{
			this->GetAtom1() = Item.GetAtom1();
			this->GetAtom2() = Item.GetAtom2();
			this->GetAtom3() = Item.GetAtom3();
		}

		return *this;
	}



	//get or set 
	U3& GetAtom3()                                                                                 { return m_Atom3; };
	U3  GetAtom3() const                                                                           { return m_Atom3; };
	void SetAtom3( IN const U3& Atom )                                                             { m_Atom3 = Atom; };
protected:

private:
	U3           m_Atom3;
};


/*
	自动释放数组
*/
#pragma region TWAutoFreeVector
template<typename U>
class TWAutoFreeVector : public vector<U*>
{
public:
	TWAutoFreeVector(): vector<U*>()     {};
	virtual ~TWAutoFreeVector()          { Free();}

public:
	//功能:深克隆
	//输入:
	//输出:
	//返回:
	//说明:使用此方法，需要元素重载“=”操作符合。
	TWAutoFreeVector<U>* DeepClone() const
	{
		TWAutoFreeVector<U>* container = new TWAutoFreeVector<U>;
		int nSize = size();
		for ( int i = 0; i < nSize; i++ )
		{
			U* pItem = at( i );
			if( pItem == NULL ) continue;
			U* pNewItem = new U;
			(*pNewItem) = *pItem;
			container->push_back( pNewItem );
		}

		return container;
	}

	//功能:从数据源拷贝数据。
	//输入:
	//输出:
	//返回:
	//说明:这是一个深拷贝
	void CopyFrom( OUT const TWAutoFreeVector<U>& Container )
	{
		//释放已有
		Free();

		//拷贝数据
		int nSize = Container.size();
		for ( int i = 0; i < nSize; i++ )
		{
			U* pItem = Container.at( i );
			if( pItem == NULL ) continue;
			U* pNewItem = new U;
			(*pNewItem) = *pItem;
			push_back( pNewItem );
		}
	}

	//功能:拷贝数据到指定容器。
	//输入:
	//输出:
	//返回:
	//说明:这是一个浅拷贝，注意生存周期
	void CopyTo( OUT vector<U*>& vRes ) const
	{
		//拷贝数据
		int nSize = size();
		for ( int i = 0; i < nSize; i++ )
			vRes.push_back( at(i) );
	}

	//功能:清理原有的元素并且释放空间
	//输入:
	//输出:
	//返回:
	//说明:
	void RemoveAllForAutoFree()          {	Free();  }

	//功能:删除元素，自动释放。
	//输入:
	//输出:
	//返回:
	//说明:	
	void EraseForAutoFree( iterator _First, iterator _Last)
	{
		iterator _Temp = _First;
		for ( ; _First != _Last; _First++ )
		{
			if( !(*_First) )
			{
				TWFreePtr( *_First );
			}
		}

		erase( _Temp, _Last );
	}

	U* SetNull( int i )
	{
		if( i < 0 || i >= size() ) return NULL;
		U* p = at( i );
		(*this)[i] = NULL;
		return p;		
	}

protected:
	void Free()
	{
		int nSize = size();
		for ( int i = 0; i < nSize; i++ )
		{
			U* pItem = at(i);
			TWFreePtr( pItem );
		}

		clear();
	}
};
#pragma endregion TWAutoFreeVector



//数组定义
//U是一个对象，不可以是指针
#pragma region CTwDimention_1Data

template<typename U>
class CTwDimention_1Data : public vector<U> 
{
public:

	CTwDimention_1Data()                                           {};
	CTwDimention_1Data( IN const CTwDimention_1Data& Atom )        { *this = Atom ;};
	~CTwDimention_1Data()                                          {}

	const CTwDimention_1Data& operator=( IN const CTwDimention_1Data& Atom )
	{
		if( this != &Atom )     assign(Atom.begin(), Atom.end() ) ;
		return *this;
	}
};

#pragma endregion CTwDimention_1Data


//二维数据定义
//U1是一维数组的类型
//U2是一维数组元素类型
#pragma region CTwDimension_2Data

template<typename U1>
class CTwDimension_2Data : public  vector<U1>
{
public:

	CTwDimension_2Data()                 {};
	~CTwDimension_2Data()                {};

	//功能:
	//输入:
	//输出:
	//返回:
	//说明:
	const U1* GetAt( IN int nRow ) const       { return &at(nRow); }
	U1* GetAt( IN int nRow )             { return &at(nRow); }

private:

	CTwDimension_2Data( IN CTwDimension_2Data& Atom )                  {}
	const CTwDimension_2Data& operator = ( IN const CTwDimension_2Data& Atom ) { return *this ;}
};

#pragma endregion CTwDimension_2Data


