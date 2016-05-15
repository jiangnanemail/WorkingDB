#pragma once

/*
	使用模板定义基本的数据结构，
	例如：一元、二元和三元的原子
	数据结构定义。
*/

//一元结构
#pragma region CUnaryAtom
template<typename U1>
class CUnaryAtom
{
public:
	CUnaryAtom():m_Atom()                                                      {};
	CUnaryAtom( IN const U1&  Atom ):m_Atom( Atom )                            {};
	~CUnaryAtom()                                                              {};

public:
	void SetAtom1( IN const U1& Atom )                                         { m_Atom = Atom;};
	U1&GetAtom1()                                                              { return m_Atom;};

	U1 GetAtom1() const                                                        { return m_Atom;};
protected:
	U1                        m_Atom;
};
#pragma endregion CUnaryAtom




//二元结构
#pragma region CBinaryAtom
template<typename U1,typename U2>
class CBinaryAtom : public CUnaryAtom<U1>
{
public:
	CBinaryAtom():CUnaryAtom<U1>(), m_Atom()                                                          {};
	CBinaryAtom( IN const U1&  Atom1, IN const U2&  Atom2 ):CUnaryAtom<U1>( Atom1 ), m_Atom( Atom2 )  {};
	~CBinaryAtom()                                                                                    {};

public:
	void SetAtom2( IN const U2& Atom )                                         { m_Atom = Atom; };
	U2& GetAtom2()                                                             { return m_Atom; };
	U2 GetAtom2() const                                                        { return m_Atom; };
protected:
	U2                        m_Atom;
};
#pragma endregion CBinaryAtom



//三元结构
#pragma region CTernaryAtom
template<typename U1, typename U2, typename U3>
class CTernaryAtom : public CBinaryAtom<U1, U2>
{
public:
	CTernaryAtom():m_Atom(),CBinaryAtom<U1, U2>()                                                  {}
	CTernaryAtom( IN const U1&  Atom1, IN const U2&  Atom2, IN const U3&  Atom3 )
		:m_Atom( Atom3 ),CBinaryAtom<U1, U2>()( Atom1, Atom2 )                                     {}
	~CTernaryAtom()                                                                                {}

public:
	void SetAtom3( IN const U3& Atom )                                                             { m_Atom = Atom; };
	U3& GetAtom3()                                                                                 { return m_Atom; };
	U3  GetAtom3() const                                                                           { return m_Atom; };
protected:
	U3                        m_Atom;
};
#pragma endregion CBinaryAtom