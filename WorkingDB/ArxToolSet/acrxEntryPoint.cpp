// (C) Copyright 2002-2005 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.h
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "./pmdx/TWDTM.h"
//-----------------------------------------------------------------------------
#define szRDS _RXST("")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CArxToolSetApp : public AcRxArxApp {

public:
	CArxToolSetApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode);
	}

	virtual void RegisterServerComponents () {
	}


	// - ArxToolSet._MyCommand1 command (do not rename)
	static void ArxToolSet_MyCommand11(void)
	{
		int n = 2000;
		int dRange = 1000;
		vertexSet  Vertices;
		triangleSet Triangles;

		for (int i = 0; i < n; i++)
		{
			double x = (double)(rand() % dRange);
			double y = (double)(rand() % dRange);
			double z = (double)(rand() % 200);
			Vertices.insert(CTwVertex(x, y, z) );
		}

		CTwDelaunay d;
		d.Triangulate(Vertices, Triangles);

		edgeSet edges;
		d.TrianglesToEdges( Triangles, edges );
		int size = edges.size();
		TWArxLineParam Ln1;

		vector<AcDbEntity*> vEnt;
		cedgeIterator IteB = edges.begin();
		cedgeIterator IteE = edges.end();
		for ( ; IteB!= IteE; IteB++ )
		{
			Ln1.m_PtStart = (IteB)->m_pV0->GetPoint();
			Ln1.m_PtEnd   = (IteB)->m_pV1->GetPoint();
			
			vEnt.push_back( Ln1.CreateEntity() );
	
		}

		TWArxEntityFun::PostCurSpace( vEnt, vector<AcDbObjectId>() );
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CArxToolSetApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CArxToolSetApp, ArxToolSet, _MyCommand11, MyCommand11, ACRX_CMD_TRANSPARENT, NULL)
