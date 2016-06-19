#pragma once

/*
	���幫������ԭ��Ԫ��
*/

/*
	��άԪ��
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
	��άԪ��
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
	�Զ��ͷ�����
*/
#pragma region TWAutoFreeVector
template<typename U>
class TWAutoFreeVector : public vector<U*>
{
public:
	TWAutoFreeVector(): vector<U*>()     {};
	virtual ~TWAutoFreeVector()          { Free();}

public:
	//����:���¡
	//����:
	//���:
	//����:
	//˵��:ʹ�ô˷�������ҪԪ�����ء�=���������ϡ�
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

	//����:������Դ�������ݡ�
	//����:
	//���:
	//����:
	//˵��:����һ�����
	void CopyFrom( OUT const TWAutoFreeVector<U>& Container )
	{
		//�ͷ�����
		Free();

		//��������
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

	//����:�������ݵ�ָ��������
	//����:
	//���:
	//����:
	//˵��:����һ��ǳ������ע����������
	void CopyTo( OUT vector<U*>& vRes ) const
	{
		//��������
		int nSize = size();
		for ( int i = 0; i < nSize; i++ )
			vRes.push_back( at(i) );
	}

	//����:����ԭ�е�Ԫ�ز����ͷſռ�
	//����:
	//���:
	//����:
	//˵��:
	void RemoveAllForAutoFree()          {	Free();  }

	//����:ɾ��Ԫ�أ��Զ��ͷš�
	//����:
	//���:
	//����:
	//˵��:	
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



//���鶨��
//U��һ�����󣬲�������ָ��
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


//��ά���ݶ���
//U1��һά���������
//U2��һά����Ԫ������
#pragma region CTwDimension_2Data

template<typename U1>
class CTwDimension_2Data : public  vector<U1>
{
public:

	CTwDimension_2Data()                 {};
	~CTwDimension_2Data()                {};

	//����:
	//����:
	//���:
	//����:
	//˵��:
	const U1* GetAt( IN int nRow ) const       { return &at(nRow); }
	U1* GetAt( IN int nRow )             { return &at(nRow); }

private:

	CTwDimension_2Data( IN CTwDimension_2Data& Atom )                  {}
	const CTwDimension_2Data& operator = ( IN const CTwDimension_2Data& Atom ) { return *this ;}
};

#pragma endregion CTwDimension_2Data


