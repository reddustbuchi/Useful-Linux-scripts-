//	Tab Size: 2
//	Comments:																								*Column 60*

#ifndef _LIB_BROWSER_H_
#define _LIB_BROWSER_H_

#ifndef __API_INTERN__
#include "c4d.h"
#else
	#include "c4d_gui.h"
	#include "ge_file.h"
	#include "c4d_baseplugin.h"
#endif
#include "c4d_library.h"


#ifndef BROWSERPLUGININTERFACE_H__

class	iBrowser {};
class	BrowserURL {};
class	ReferenceObject {};
class	RTreeNode {};
class	BrowserContentNode {};
class BrowserPluginInterface {};

#else

class	iBrowser;
class	BrowserURL;
class	ReferenceObject;
class	RTreeNode;
class	BrowserContentNode;
class BrowserPluginInterface;

#endif

class GvNode;

//----------------------------------------------------------------------------------------
// URL for locations in the file system (and virtual places somewhere in the browser)
//----------------------------------------------------------------------------------------
#ifdef BROWSERPLUGININTERFACE_H__
#define	SDKBrowserURL BrowserURL
#else
class SDKBrowserURL
{
private:
	C4D_RESERVE_PRIVATE_TYPE(Int32,dummy1);
	C4D_RESERVE_PRIVATE_TYPE(UInt32,dummy2);
	C4D_RESERVE_PRIVATE_TYPE(Filename,dummy3);
	C4D_RESERVE_PRIVATE_TYPE(String,dummy4);
	C4D_RESERVE_PRIVATE_TYPE(Int32,dummy5);
	C4D_RESERVE_PRIVATE_TYPE(Int32,dummy6);
	C4D_RESERVE_PRIVATE_TYPE(void*,dummy7);

public:
	void	*GetPrivate( void )	const;

	SDKBrowserURL( void );
	SDKBrowserURL( const SDKBrowserURL &src );
	SDKBrowserURL( const Filename &src );
	SDKBrowserURL( const String &src );

	~SDKBrowserURL( void );

	const SDKBrowserURL 				&operator = ( const SDKBrowserURL &cs );
	const SDKBrowserURL					operator + ( const String &str2 ) const;
	const SDKBrowserURL					&operator += ( const String &str );
	Bool												operator == ( const SDKBrowserURL &url ) const;
	Bool												operator != ( const SDKBrowserURL &url ) const;

	Bool					Content( void ) const;
	SDKBrowserURL	GetDirectory( void ) const;
	String			GetFileString( void ) const;
	Bool				IsFilename( void ) const;
	Bool				CheckSuffix( const String &s ) const;
	String			GetSuffix( void ) const;

	void	SetFilename( const Filename &f );

	/*
		SetString()
		-	set a file name as	"file://localhost/..."
		-	set a preset location as "preset:// * /..." where * is the catalog name
		-	set a catalog location as "catalog:// * /..." where * is the catalog name
	*/
	void	SetString( const String &s );

	/*
		GetFilename() will return true if the URL contains a filename (or a file:// string)
		and return that name in <f>. If the URL string is a catalog location or something
		else in the	browser tree it will return false.
	*/
	Bool	GetFilename( Filename &f ) const;

	/*
		Will return an empty Filename if the URL does not contain a file name
	*/
	Filename	GetFilename( void ) const;

	/*
		GetString()
			-	returns a file name as	"file://localhost/..."
			-	returns a catalog location as "catalog:// * /..." where * is the catalog name
	*/
	void		GetString( String &s ) const;
	String	GetString( void ) const;

};

#endif

#ifdef	BROWSERPLUGININTERFACE_H__
#define	SDKBrowserIcon					BrowserIcon
#else
class	SDKBrowserIcon
{
public:
	BaseBitmap	*GetBaseBitmap( void );
	static void	Free( SDKBrowserIcon *icon );
};
#endif

//----------------------------------------------------------------------------------------
// base class for the browser nodes
//----------------------------------------------------------------------------------------
class SDKReferenceObject
{
private:
	SDKReferenceObject( void );
	virtual	~SDKReferenceObject( void );
public:
	void	add_reference( void );
	void	remove_reference( void );
};

#include "sdkreferenceobjectptr.h"

//----------------------------------------------------------------------------------------
// basic tree node
//----------------------------------------------------------------------------------------
class SDKRTreeNode;
typedef SDKReferenceObjectPtr<SDKRTreeNode>	SDKRTreeNodeRef;

class SDKRTreeNode : public SDKReferenceObject
{
	SDKRTreeNode( void );
	~SDKRTreeNode( void );
public:
	SDKRTreeNodeRef	GetUp( void );
	SDKRTreeNodeRef	GetDown( void );
	SDKRTreeNodeRef	GetNext( void );
	SDKRTreeNodeRef	GetPred( void );

	void	InsertUnder( SDKRTreeNodeRef parent );
	void	Remove( void );
};

//////////////////////////////////////////////////////////////////////////

#ifdef	BROWSERPLUGININTERFACE_H__
#define	SDKBrowserPluginRef			BrowserPluginRef
#define SDKBrowserContentNodeRef	BrowserContentNodeRef
#define	SDKBrowserPreviewData	BrowserPreviewData
#define	SDKBrowserPreviewInfo	BrowserPreviewInfo
#define	SDKBrowserPluginInterface	BrowserPluginInterface

#else
class SDKBrowserContentNode;
typedef SDKReferenceObjectPtr<SDKBrowserContentNode>	SDKBrowserContentNodeRef;
#endif


#ifndef	BROWSERPLUGININTERFACE_H__

#define	BrowserBaseFileURL		"file://localhost"
#define	BrowserBaseCatalogURL	"catalog:/"
#define	BrowserBasePresetURL	"preset:/"
#define	BrowserBaseRecentURL	"recent:/"
#define	BrowserBaseSearchURL	"search:/"

// language codes
enum
{
	LanguageDefault = 0,
	LanguageUS	= 0x75730000,																	// 'us/0/0'
	LanguageDE	= 0x64650000,																	// 'de/0/0'
	LanguageJP	= 0x6a700000,																	// 'jp/0/0'
	LanguageCZ	= 0x637a0000,																	// 'cz/0/0'
	LanguageES	= 0x65730000,																	// 'es/0/0'
	LanguageFR	= 0x66720000,																	// 'fr/0/0'
	LanguageIT	= 0x69740000,																	// 'it/0/0'
	LanguagePL	= 0x706c0000																	// 'pl/0/0'
};

//----------------------------------------------------------------------------------------
// Interface base class of a browser plugin
//----------------------------------------------------------------------------------------
enum																												// basic plugins for the browser
{
	CBPluginTypeImage = 1018021,
	CBPluginTypeMovie = 1018022,
	CBPluginTypeScene = 1018023,
	CBPluginTypeCategory = 1018024,
	CBPluginTypeCatalog = 1018025,
	CBPluginTypeUnknown = 1018026,
	CBPluginTypeFolder  = 1018027,
	CBPluginTypeMaterial = 1018028,
	CBPluginTypeDummy = 1018029,
	CBPluginTypeDefaults = 1018030,
	CBPluginTypeFilePreset = 1018031,
	CBPluginTypeObjectPreset = 1018107,
	CBPluginTypeMaterialPreset = 1018108,
	CBPluginTypeTagPreset = 1018109,
	CBPluginTypeRenderDataPreset = 1018110,
	CBPluginTypeShaderPreset = 1018111,
	CBPluginTypeVideoPostPreset = 1018112,
	CBPluginTypeXPressoPreset = 1018113,
	CBPluginTypePresetLibrary = 1018760,
	CBPluginTypeCatalogFile = 1018761,
	CBPluginTypeScriptFile =	1018762
};

typedef void	SDKBrowserPreviewData;

struct	SDKBrowserPreviewInfo
{
	enum
	{
		DefaultQuality	= 0x00,																	// get whatever quality is available
		LowQuality			=	0x01,																	// a low quality preview is available
		MediumQuality		= 0x02,																	// a medium quality preview is available
		HighQuality			= 0x04,																	// a high quality preview is available
		MaximumQuality	= 0x08,																	// a maximum quality preview is available (high render times!)
		QualityMask			= 0x0f,

		FixedSize				= 0x80000000														// set if the preview size is fixed (e.g. image files)
	};
	Int32	quality_flags;
	Int32	max_width;																					// maximum width of the preview bitmap (or 0 if resolution independent)
	Int32	max_height;																					// maximum height of the preview bitmap (or 0 if resolution independent)
};

class SDKBrowserPluginInterfaceInfo;
class SDKBrowserPluginInterface;
typedef SDKBrowserPluginInterface	*SDKBrowserPluginRef;

class SDKBrowserPluginInterface
{
public:
	enum
	{
		// basic tabs
		PreviewTab = 0,
		InfoTab,

		// plugin-specific tabs
		PrivateTab0 = 65536,
		PrivateTab1,
		PrivateTab2,
		PrivateTab3,
		PrivateTab4,
		PrivateTab5,
		PrivateTab6,
		PrivateTab7
	};

	// Definitions for GetTypeName
	enum
	{
		BasicItemType					=	1,															// the basic item type (i.e. image, or sound file), this string is language dependant
		SpecificItemType			= 2,															// more specific item type, like "JPEG image file", this string is language dependant
		HierarchicalItemType	= 3																//
	};

	// Definitions for Identify
	enum
	{
		SlowIdentification		= 0x01														// you are allowed to try the best possible identifaction - even if it's slow
	};

	// Flags for Open
	enum
	{
		Merge									= 0x01
	};

	static SDKBrowserPluginRef	Alloc( SDKBrowserPluginInterfaceInfo *plugin_info );
	static void									Free( SDKBrowserPluginRef &plugin );


	Int32						GetPluginID( String *plugin_name = 0 ) const;	// Return the ID of the plugin (unique ID from plugincafe.com), plugin_name can be zero
	Bool						Identify( const SDKBrowserURL &url, UChar *probe, Int32 size, UInt32 flags );	// Identify a file and return true, if the plugin is able to deal with the file
	String					GetTypeName( const SDKBrowserContentNodeRef node, const SDKBrowserURL *url, Int32 mode );	// Return the kind of data that will be handled by this plugin. For example "Image", "Scene", "Material" ...  (please note: either node or url can be zero!)
	String					*GetTypeNames( Int32 mode, Int32 *no_strings );

	SDKBrowserPreviewData	*OpenPreviewBitmap( BaseThread *thread, const SDKBrowserContentNodeRef node, const SDKBrowserURL *url, SDKBrowserPreviewInfo *info );
	void								ClosePreviewBitmap( SDKBrowserPreviewData *data );
	BaseBitmap					*GetPreviewBitmap( SDKBrowserPreviewData *data, Int32 w, Int32 h, Int32 quality );

	SDKBrowserIcon	*GetIcon( const SDKBrowserURL &url, Int32 pref_wh = 0 );	// Return an icon for this kind of file (does not have to be a preview for this specific file)

	SubDialog				*OpenPreviewDialog( SDKBrowserContentNodeRef node, Int32 tab_id );	// Return a plugin specific preview subdialog for the content node.
	Int32						ClosePreviewDialog( SDKBrowserContentNodeRef node, SubDialog *s );	// Will be called when the preview is not used anymore
	Int32						UpdatePreviewDialog( SDKBrowserContentNodeRef node, SubDialog *s );	// Will be called to update the current preview
	Bool						Open( SDKBrowserContentNodeRef node, const SDKBrowserURL *url, Int32 flags );	// Open a content node
};

#endif

class SDKBrowserPluginInterfaceInfo
{
	friend class SDKBrowser;

private:
	SDKBrowserPluginRef	plugin;

public:
	SDKBrowserPluginInterfaceInfo( void );
	SDKBrowserPluginRef	GetPlugin( void ) const;

	enum
	{
		// basic tabs
		PreviewTab = 0,
		InfoTab,

		// plugin-specific tabs
		PrivateTab0 = 65536,
		PrivateTab1,
		PrivateTab2,
		PrivateTab3,
		PrivateTab4,
		PrivateTab5,
		PrivateTab6,
		PrivateTab7
	};

	// Definitions for GetTypeName
	enum
	{
		BasicItemType					=	1,															// the basic item type (i.e. image, or sound file), this string is language dependant
		SpecificItemType			= 2,															// more specific item type, like "JPEG image file", this string is language dependant
		HierarchicalItemType	= 3																//
	};

	// Definitions for Identify
	enum
	{
		SlowIdentification		= 0x01														// you are allowed to try the best possible identifaction - even if it's slow
	};

	// Flags for Open
	enum
	{
		Merge									= 0x01
	};

	virtual Int32						GetPluginID( String *plugin_name = 0 ) = 0;	// Return the ID of the plugin (unique ID from plugincafe.com), plugin_name can be zero
	virtual Bool						Identify( const SDKBrowserURL &url, UChar *probe, Int32 size, UInt32 flags ) = 0;	// Identify a file and return true, if the plugin is able to deal with the file
	virtual String					GetTypeName( const SDKBrowserContentNodeRef node, const SDKBrowserURL *url, Int32 mode ) = 0;	// Return the kind of data that will be handled by this plugin. For example "Image", "Scene", "Material" ...  (please note: either node or url can be zero!)
	virtual String					*GetTypeNames( Int32 mode, Int32 *no_strings ) = 0;

	virtual SDKBrowserPreviewData	*OpenPreviewBitmap( BaseThread *thread, const SDKBrowserContentNodeRef node, const SDKBrowserURL *url, SDKBrowserPreviewInfo *info ) = 0;
	virtual void						ClosePreviewBitmap( SDKBrowserPreviewData *data ) = 0;
	virtual BaseBitmap			*GetPreviewBitmap( SDKBrowserPreviewData *data, Int32 w, Int32 h, Int32 quality ) = 0;

	virtual SDKBrowserIcon	*GetIcon( const SDKBrowserURL &url, Int32 pref_wh = 0 ) = 0;	// Return an icon for this kind of file (does not have to be a preview for this specific file)

	virtual SubDialog				*OpenPreviewDialog( SDKBrowserContentNodeRef node, Int32 tab_id ) = 0;	// Return a plugin specific preview subdialog for the content node.
	virtual Int32						ClosePreviewDialog( SDKBrowserContentNodeRef node, SubDialog *s ) = 0;	// Will be called when the preview is not used anymore
	virtual Int32						UpdatePreviewDialog( SDKBrowserContentNodeRef node, SubDialog *s ) = 0;	// Will be called to update the current preview
	virtual Bool						Open( SDKBrowserContentNodeRef node, const SDKBrowserURL *url, Int32 flags ) = 0;	// Open a content node


};

//----------------------------------------------------------------------------------------
// Node info for SDK browser content nodes
//----------------------------------------------------------------------------------------
#ifdef	BROWSERPLUGININTERFACE_H__
#define	SDKBrowserContentNodeInfo BrowserContentNodeInfo
#else

typedef Int32	CopyMoveCallback( void *private_data, Int32 msg, Int32 item_cnt, Int64 item_size, void *reserved );
#endif

class SDKBrowserContentNodeInfo
{
	friend class	SDKBrowserContentNode;
	friend class 	SDKNode;

private:
	Int32	plugin_id;
	void	*node;
public:

// administration methods
	SDKBrowserContentNodeInfo( Int32 plugin_id );
	SDKBrowserContentNodeRef	GetNode( void ) const;				// return the corresponding node
	virtual Bool		Init( void *node );											// called by the browser with pointer to the corresponding node
	virtual void		Free( void );														// will be called by the browser before the node will be deleted (override this if you want to dispose of the SDKBrowserContentNodeInfo at a later time)


// the content methods
	virtual Int32		GetTypeID( void ) = 0;									// type of content node
	virtual SDKBrowserPluginRef	GetPlugin( UInt32 flags = 0 ) = 0;	// plugin that can deal with this file

	virtual String	GetName( void ) = 0;										// Return the name of the content node (used in the UI)
	virtual String	GetTypeName( Int32 mode );
	virtual Int32		GetNodeURL( SDKBrowserURL &url, UInt32 flags = 0 ) const = 0;
	virtual Bool		GetNodeTime( UInt32 mode, LocalFileTime *out ) = 0;
	virtual UInt32		GetNodeFlags( Int64 *out_size = 0 ) = 0;	// Return a few node flags (see IsDirectory)

	virtual SDKBrowserIcon	*GetIcon( Int32 flags = 0, Int32 pref_wh = 0 ) = 0; //icon for this kind of file

	virtual Int32		UpdateDirectory( void ) = 0;

	virtual Int32		PrivateCall( Int32 plugin_id, Int32 node_type, Int32 selector, void *data );	// Hook for private calls

	enum
	{
		CheckOperation 		= 0,																	// check if the node (and its children) can be moved/copied/deleted (to the requested destination)
		PrepareOperation 	= 1,																	// collect information about the number of items and their size
		PerformOperation	= 2,																	// perform the move/copy/delete operation

		ModeMask					= 0x0000ffff,													// mask for the mode

		ModePrivateFlag1	= 0x01000000,													// private node type specific flags for internal use only
		ModePrivateFlag2	= 0x02000000,
		ModePrivateFlag3	= 0x04000000,
		ModePrivateFlag4	= 0x08000000,
		ModePrivateFlag5	= 0x10000000,
		ModePrivateFlag6	= 0x20000000,
		ModePrivateFlag7	= 0x40000000
	};

	enum
	{
		OperationSuccessful				= 0,

		RenameNotPermitted				=	-2147483647,								// 0x80000001,
		MoveNotPermitted					=	-2147483646,								// 0x80000002,
		CopyNotPermitted					=	-2147483644,								// 0x80000004,
		DeleteNotPermitted				= -2147483640,								// 0x80000008,
		NewFolderNotPermitted			= -2147483632,								// 0x80000010,

		RenameError								=	-2147483392,								// 0x80000100,
		MoveError									=	-2147483136,								// 0x80000200,
		CopyError									=	-2147482624,								// 0x80000400,
		DeleteError								=	-2147481600,								// 0x80000800,

		UnsupportedNodeType				=	-1610612736,								// 0xa0000000L,
		UserCancelled							=	-1073741824									// 0xc0000000L,
	};

	// only CheckOperation/PerformOperation
	virtual	Int32	Rename( Int32 mode, const String &name )
	{
		return(RenameNotPermitted );
	}

	// only CheckOperation/PerformOperation
	virtual Int32	NewFolder( Int32 mode, const String &name, SDKBrowserContentNodeRef *folder = 0 )
	{
		return((Int32) ( NewFolderNotPermitted ));
	}

	/*
		Calls for moving, copying or deleting nodes
		callback is only called for PrepareOperation and PerformOperation
	*/
	virtual	Int32	MoveFrom( SDKBrowserContentNodeRef new_child, Int32 mode, CopyMoveCallback *callback, void *private_data, BaseThread *thread )
	{
		return((Int32) ( MoveNotPermitted ));
	}

	virtual	Int32	CopyFrom( SDKBrowserContentNodeRef new_child, Int32 mode, const String *rename, CopyMoveCallback *callback, void *private_data, BaseThread *thread )
	{
		return((Int32) ( CopyNotPermitted ));
	}

	virtual Int32	Delete( Int32 mode, CopyMoveCallback *callback, void *private_data, BaseThread *thread )
	{
		return((Int32) ( DeleteNotPermitted ));
	}

	virtual ~SDKBrowserContentNodeInfo() {}	// a dummy to make the compiler happy
};

//----------------------------------------------------------------------------------------
// SDK browser content node
//----------------------------------------------------------------------------------------
#ifdef	BROWSERPLUGININTERFACE_H__
#define SDKBrowserContentNode BrowserContentNode
#else

#define	LinkThrough	 0x80000000															// return the linked data, for example the "real" plugin for a linked node (in case of a catalog item)

class SDKBrowserContentNode : public SDKRTreeNode
{
private:
	SDKBrowserContentNode( void );														// use Alloc!
	~SDKBrowserContentNode( void );														// nodes will be disposed of when they are not used anymore ...
public:

	static SDKBrowserContentNodeRef	Alloc( SDKBrowserContentNodeInfo *info, SDKBrowserContentNodeRef parent = 0 );
	static SDKBrowserContentNodeRef	AllocCategoryNode( const String &name, const String &local_path, const Filename &icon_file = Filename(), SDKBrowserContentNodeRef parent = 0 );
	static void											FreeNodes( Int32 plugin_id );	// free all SDKBrowserContentNodeInfo of this plugin and remove the nodes from the tree
	SDKBrowserContentNodeInfo				*GetNodeInfo( Int32 plugin_id = 0 ) const;	// return the SDKBrowserContentNodeInfo for this node (or 0 )

	// Definitions for GetTypeID
	enum
	{
		TypeUnknown = 0,
		TypeCategory,																						// node is a category folder
		TypeFileSystem,																					// node represent a file or folder in the file system
		TypePreset,																							// node represents some kind of setting/preset
		TypeCatalog,																						// this is a catalog node (that might link to another node)
		TypeMaterial																						// this is virtual material node
	};

	// Definitions for GetNodeFlags
	enum
	{
		Directory 				= 0x01,																// is a directory (or generally speeking a tree branch)
		VirtualDirectory	= 0x02,																// is file that contains data that is displayed as children (e.g. a material library)
		VirtualFile				= 0x04,																// is a directory that is represented as a file
		Link							= 0x08,																// this node is a link to a source node (e.g. a catalog node)
		ReadOnly					= 0x10,																// this node cannot be modified
		Flush							= 0x40,																// this node is likely to be deleted soon
		NoPreview					= 0x80,																// a preview for this item is and will not be available (unknown file format)

		PrivateFlag0			=	0x010000,														// these flags are private, a node (and the corresponding) plugin
		PrivateFlag1			=	0x020000,														// can use them for whatever is appropriate
		PrivateFlag2			=	0x040000,
		PrivateFlag3			=	0x080000,

		TargetNotFound		= 0x20000000,													// if the file (node) linked by a catalog cannot be found
		KeepResident			= 0x40000000
	};

	// Definitions for GetIcon
	enum
	{
		IconNone 					= 0x0000,
		IconPreviewBitmap	= 0x8000,
		IconFolderOpen		= 0x0001
	};

	// Definitions for GetTypeName
	enum
	{
		BasicItemType					=	1,															// the basic item type (i.e. image, or sound file), this string is language dependant
		SpecificItemType			= 2,															// more specific item type, like "JPEG image file", this string is language dependant
		HierarchicalItemType	= 3																//
	};

	enum
	{
		LazyIdentification = 0x02																// for GetPlugin()  only
	};

	Int32	GetTypeID( void ) const;														// type of content node
	SDKBrowserPluginRef	GetPlugin( UInt32 flags = 0 ) const;		// Return pointer to the plugin that can deal with this file (see g)
	String	GetName( void ) const;														// Return the name of the content node (used in the UI)
	String	GetTypeName( Int32 mode ) const;										// Return a description of the file type, e.g. "Image", "Web page" or "3D Scene"

	/*
		Returns the URL of the content node (this is the file name if the node represents
		a file or folder in the file system). If there are multiple objects in a file
		(e.g. presets) the return value reflects the index
	*/
	Int32					GetNodeURL( SDKBrowserURL &url, UInt32 flags = 0 ) const;
	SDKBrowserURL	GetNodeURL( UInt32 flags = 0, Int32 *idx = 0 ) const;
	Bool					GetFilename( Filename &f, UInt32 flags = 0 ) const;

	/*
		Returns the creation and last modification time of a node (this will usually
		be the file times). For a directory the modification time will usually be the
		time, when a file has been added or removed.
	*/
	Bool					GetNodeTime( UInt32 mode, LocalFileTime *out ) const;
	LocalFileTime	GetNodeTime( UInt32 mode = GE_FILETIME_MODIFIED ) const;
	UInt32					GetNodeFlags( Int64 *out_size = 0 ) const;	// Return a few node flags (see IsDirectory)
	Bool					IsDirectory( void ) const;
	Bool					IsLink( void ) const;
	Bool					IsReadOnly( void ) const;
	Bool					IsFlushed( void ) const;

	SDKBrowserIcon	*GetIcon( Int32 state = 0, Int32 pref_wh = 0 ) const;	// Return an icon for this kind of file (does not have to be a preview for this specific file)	pref_wh is the preferred icon size

	Int32	UpdateDirectory( void );														// ...will be called, before GetDown() is used to search for children (mainly for file system based trees)

	Int32	PrivateCall( Int32 plugin_id, Int32 node_type, Int32 selector, void *data );	// Hook for private calls
	enum
	{
		CheckOperation 		= 0,																	// check if the node (and its children) can be moved/copied/deleted (to the requested destination)
		PrepareOperation 	= 1,																	// collect information about the number of items and their size
		PerformOperation	= 2																		// perform the move/copy/delete operation
	};

	enum
	{
		OperationSuccessful				= 0,

		RenameNotPermitted				=	-2147483647,								// 0x80000001,
		MoveNotPermitted					=	-2147483646,								// 0x80000002,
		CopyNotPermitted					=	-2147483644,								// 0x80000004,
		DeleteNotPermitted				= -2147483640,								// 0x80000008,
		NewFolderNotPermitted			= -2147483632,								// 0x80000010,

		RenameError								=	-2147483392,								// 0x80000100,
		MoveError									=	-2147483136,								// 0x80000200,
		CopyError									=	-2147482624,								// 0x80000400,
		DeleteError								=	-2147481600,								// 0x80000800,

		UnsupportedNodeType				=	-1610612736,								// 0xa0000000L,
		UserCancelled							=	-1073741824									// 0xc0000000L,
	};

	/*
		Calls for moving, copying or deleting nodes
		callback is only called for PrepareOperation() and PerformOperation()
	*/
	Int32	Rename( Int32 mode, const String &name );
	Int32	NewFolder( Int32 mode, const String &name, SDKBrowserContentNodeRef *folder = 0 );
	Int32	MoveFrom( SDKBrowserContentNodeRef new_child, Int32 mode, CopyMoveCallback *callback, void *private_data, BaseThread *thread = nullptr );
	Int32	CopyFrom( SDKBrowserContentNodeRef new_child, Int32 mode, const String *rename, CopyMoveCallback *callback, void *private_data, BaseThread *thread = nullptr );
	Int32	Delete( Int32 mode, CopyMoveCallback *callback, void *private_data, BaseThread *thread = nullptr );

	// node/plugin specific calls
	BaseObject			*GetDefaultObject( void );
	BaseDocument		*GetObjectPreset( void );
	BaseMaterial		*GetMaterialPreset( void );
	BaseTag					*GetTagPreset( void );
	RenderData			*GetRenderDataPreset( void );
	BaseShader		*GetShaderPreset( void );
	BaseVideoPost	*GetVideoPostPreset( void );
	GvNode					*GetXPressoPreset( void );
	Int32						GetPresetSourcePluginID( void );
};
#endif

#define	DRAGTYPE_BROWSER	1017705														// Browser Drag Message

class SDKBrowserDragInfo
{
private:
	SDKBrowserDragInfo( void );
	~SDKBrowserDragInfo( void );

public:
	Int32	GetItemCount( void )
	{
		return( no_items );
	}

	SDKBrowserContentNodeRef	GetItem( Int32 idx )
	{
		if (( idx >= 0 ) && ( idx < no_items ))
			return( items[idx] );

		return (SDKBrowserContentNode *) nullptr;
	}

	Int32											no_items;												// number of dragged objects
	Int32											reserved1;
	SDKBrowserContentNodeRef	*items;													// array with SDKBrowserContentNodeRefs of the dragged objects
	void											*reserved3;
};


//////////////////////////////////////////////////////////////////////////

#define	SDKBROWSER_MIN_GADGET_ID	1000000										// this is the minimum id for additional gadgets in the preview sub dialog

class SDKBrowserPreviewDialog : public SubDialog
{
public:
	enum
	{
		DontUpdatePreviewBitmap	= 0x1														// for Update() if you use a custom preview bitmap
	};

	SDKBrowserPreviewDialog( void );
	virtual	~SDKBrowserPreviewDialog( void );

	// function
	void	Init( SDKBrowserContentNodeRef content, Int32 tab_id );
	Bool	Update( Int32 flags = 0 );
	Bool	AddTab( Int32 id, const String &name );							// add an extra tab (must be call before CreateLayout!)
	Bool	RemoveDefaultTab( Int32 id );												// remove one of the default Tabs (PreviewTab, InfoTab)
	Bool	LayoutFlushTab( Int32 id );													// flush content of one of the default Tabs and  (PreviewTab, InfoTab)
	Bool	LayoutAddToTab( Int32 id );													// set insertion point at the end of one of the default tabs ...
	Bool	LayoutChangedTab( Int32 id );												// flush content of one of the default Tabs and  (PreviewTab, InfoTab)
	Int32	GetActiveTab( void );																// return the id of the active tab
	void	ChangePreviewBitmap( BaseBitmap *bm, Int32 flags = 0 );


	// for overriding (for easy message handling)
	virtual Bool CreateLayout( void );
	virtual Bool InitValues( void );
	virtual Bool CoreMessage( Int32 id, const BaseContainer &msg );
	virtual Bool Command( Int32 id,const BaseContainer &msg );
	virtual Bool AskClose( void );
	virtual void Timer( const BaseContainer &msg );
	virtual void DestroyWindow( void ); 											// use this function to set all pointers to userareas/customgui elements to nullptr

	// for overriding (for special message handling)
	virtual Int32 Message( const BaseContainer &msg, BaseContainer &result );

private:
	void	*private_data;
};


//////////////////////////////////////////////////////////////////////////

#ifdef	BROWSERPLUGININTERFACE_H__
#define SDKBrowsePresets BrowseURL
#else

class SDKBrowsePresets
{
private:
	SDKBrowsePresets( void );
	~SDKBrowsePresets( void );

public:
	static SDKBrowsePresets	*Alloc( Int32 db_index );
	static void	Free( SDKBrowsePresets *browse_presets );

	Bool	GetNext( SDKBrowserURL &url, Int32 &plugin_id );
};

#endif

//////////////////////////////////////////////////////////////////////////


enum
{
	SDKBrowserPreviewDialogAlloc = 0,
	SDKBrowserPreviewDialogFree,
	SDKBrowserPreviewDialogInit,
	SDKBrowserPreviewDialogAddTab,
	SDKBrowserPreviewDialogRemoveDefaultTab,
	SDKBrowserPreviewDialogLayoutFlushTab,
	SDKBrowserPreviewDialogLayoutAddToTab,
	SDKBrowserPreviewDialogLayoutChangedTab,
	SDKBrowserPreviewDialogGetActiveTab,
	SDKBrowserPreviewDialogChangePreviewBitmap,
	SDKBrowserPreviewDialogCreateLayout,
	SDKBrowserPreviewDialogInitValues,
	SDKBrowserPreviewDialogCoreMessage,
	SDKBrowserPreviewDialogCommandNotifyEx,
	SDKBrowserPreviewDialogCommand,
	SDKBrowserPreviewDialogAskClose,
	SDKBrowserPreviewDialogTimer,
	SDKBrowserPreviewDialogDestroyWindow,
	SDKBrowserPreviewDialogMessage,
	SDKBrowserPreviewDialogUpdate
};

class SDKBrowser
{
private:

	SDKBrowser();
	~SDKBrowser();

public:
	enum
	{
		CategoryPresetNodes 	= 0,
		CategoryCatalogNodes	= 1,
		CategoryDriveNodes 		= 2,
		CategoryRecentNodes 	= 3,
		CategorySearchNodes		= 4,

		ddumdumdimdum
	};

	// for FindNode
	enum
	{
		FindExactMatch =				1,
		FindBestMatch = 				2,
		ForceDirectoryUpdate = 	4
	};

	enum
	{
		Computer	= 0,
		Drive,
		DriveCD,
		Folder,
		FolderOpen,
		FolderPresets,
		FolderCatalogs,
		FolderSearch,
		Document,
		ThreeDFile,
		ImageFile,
		MovieFile,
		Preset
	};

	// for GetDbIndex, LoadPreset, SavePreset, DeletePreset, ChangePresetURL, GetPresetName, SetPresetName, GetPresetAnnotation, SetPresetAnnotation, CreatePresetNode
	enum
	{
		UserPresetDb = 				1,
		InvalidPresetDb = 		-1
	};

	// for MountPresetLibrary
	enum
	{
		ReadOnlyPresetLibrary	= 1,															// disables write operations to the preset library (regardless of the file system settings)
		SystemPresetLibrary		= 2,
		IgnoreROPresetLibrary = 4																// ignores a readonly flag in the preset library and makes it writable
	};

	// for SetPresetPreview()
	enum
	{
		PreviewReplace = 0,
		PreviewAppend = 1
	};

	typedef SDKBrowserContentNodeRef	InsertNodeFromDataBase( SDKBrowserContentNodeRef parent, SDKBrowserContentNodeRef existing_node, const SDKBrowserURL &url, const String &name, UInt32 flags, Int32 db_index, void *user_data );

	static Bool						OpenNewBrowser( const SDKBrowserURL &path, UInt32 flags = 0 );
	static SDKBrowserContentNodeRef	GetCategoryNode( Int32 where );

	static SDKBrowserIcon	*GetIcon( Int32 id, Int32 pref_wh = 0 );
	static SDKBrowserIcon	*GetIcon( const SDKBrowserURL &url, SDKBrowserPluginRef plugin = 0, Int32 flags = 0, LocalFileTime *preview_time = 0 );
	static SDKBrowserIcon	*GetPreviewIcon( SDKBrowserContentNodeRef content, Int32 pref_wh, Int32 flags = SDKBrowserContentNode::IconPreviewBitmap );
	static SDKBrowserIcon	*CreateIcon( BaseBitmap *bm, Bool dont_free );
	static void						ReleaseIcon( SDKBrowserIcon *icon );

	static Bool						RegisterBrowserPlugin( SDKBrowserPluginInterfaceInfo *plugin_info, UInt32 flags = 0 );
	static Bool						UnregisterBrowserPlugin( SDKBrowserPluginInterfaceInfo *plugin_info );

	static Int32						RegisterPresetLibrary( const SDKBrowserURL &domain, const String &name, const Filename &f );
	static Bool						UnregisterPresetLibrary( Int32 db_index, const Filename &f );
	static Int32						GetDbIndex( const SDKBrowserURL &url, UInt32 flags = 0 );
	static Bool						ExistsPreset( const SDKBrowserURL &url );
	static Bool						LoadPreset( Int32 db_index, const SDKBrowserURL &url, Int32 &plugin_id, BaseContainer *bc, void **data, Int *length );
	static Bool						SavePreset( Int32 db_index, const SDKBrowserURL &url, Int32 plugin_id, const BaseContainer *bc, void *data, Int length );
	static Bool						DeletePreset( Int32 db_index, const SDKBrowserURL &url, Int32 plugin_id );
	static Bool						CopyPreset( const SDKBrowserURL &src, const SDKBrowserURL &dst );
	static Bool						GetPresetName( Int32 db_index, const SDKBrowserURL &url, Int32 language_id, String &out_name );
	static Bool						SetPresetName( Int32 db_index, const SDKBrowserURL &url, Int32 language_id, const String &name );
	static Bool						ChangePresetURL( Int32 db_index, const SDKBrowserURL &url, const SDKBrowserURL &new_url, Int32 plugin_id );
	static Bool						GetPresetAnnotation( Int32 db_index, const SDKBrowserURL &url, String &annotation );
	static Bool						SetPresetAnnotation( Int32 db_index, const SDKBrowserURL &url, const String &annotation );
	static Bool						SetPresetPreview( Int32 db_index, const SDKBrowserURL &url,  Int32 mode, Int32 preview_quality, BaseBitmap *bm, const LocalFileTime *lft );
	static BaseBitmap			*GetPresetPreview( Int32 db_index, const SDKBrowserURL &url, Int32 frame_idx );
	static Bool						GetPresetAnimationData( Int32 db_index, const SDKBrowserURL &url, Int32 *first_frame_idx, Int32 *last_frame_idx, Float *fps );
	static Bool						SetPresetAnimationData( Int32 db_index, const SDKBrowserURL &url, Int32 first_frame_idx, Int32 last_frame_idx, Float fps );

	static Bool						SavePresetObject( const SDKBrowserURL &url, BaseList2D *bl );
	static Bool						ReadNodesFromDatabase( Int32 db_index, const SDKBrowserURL &base_url, SDKBrowserContentNodeRef base_node, InsertNodeFromDataBase *callback, void *user_data );
	static Bool						CreatePresetNode( Int32 db_index, const SDKBrowserURL &url, Int32 plugin_id, Int32 mode = 0 );
	static Bool						SetPresetSortOrder(SDKBrowserContentNodeRef *nodes, Int32 cnt );

	static Bool						MountPresetLibrary( const Filename &fn, UInt32 flags, SDKBrowserURL *domain = nullptr );

	static void						UpdateNotification( SDKBrowserContentNodeRef node, Int32 flags = 0 );

	static Int32						PreviewDialogMisc( SubDialog *dlg, void *&private_data, Int32 cmd, Int32 value0 = 0, Int32 value1 = 0, void *value2 = 0, void *value3 = 0 );

	static SDKBrowserContentNodeRef	FindNode( const SDKBrowserURL &url, Int32 flags = FindExactMatch, SDKBrowserContentNodeRef start_from  = 0 );

	static Bool 					Identify( const SDKBrowserURL &url, UInt32 flags, SDKBrowserPluginRef *plugin_out );

	static BaseList2D 		*GetDefaultObject( Int32 id, UInt32 flags = 0 );
	static Bool 					SetDefaultObject( BaseList2D *bl, UInt32 flags = 0 );
	static Bool						OpenNewBrowserWithTitle( const SDKBrowserURL &path, const String& custom_title = String(), UInt32 flags = 0 );
};

//////////////////////////////////////////////////////////////////////////

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#define	BROWSER_LIB_ID	1017645

struct BrowserMethods
{
	Bool 						(*OpenNewBrowser)( const SDKBrowserURL &url, UInt32 flags );
	SDKBrowserContentNodeRef	(*GetCategoryNode)( Int32 where );

	SDKBrowserIcon	*(*GetStaticIcon)( Int32 id, Int32 pref_wh );
	SDKBrowserIcon	*(*GetIcon)( const SDKBrowserURL &url, SDKBrowserPluginRef plugin, Int32 flags, LocalFileTime *preview_time );
	SDKBrowserIcon	*(*GetPreviewIcon)( SDKBrowserContentNodeRef content, Int32 pref_wh, Int32 flags );
	SDKBrowserIcon	*(*CreateIcon)( BaseBitmap *bm, Bool dont_free );
	void						(*ReleaseIcon)( SDKBrowserIcon* icon );

	Int32						(*RegisterPresetLibrary)( const SDKBrowserURL &domain, const String &name, const Filename &f );
	Bool						(*UnregisterPresetLibrary)( Int32 db_index, const Filename &f );
	Bool						(*LoadPreset)( Int32 db_index, const SDKBrowserURL &url, Int32 &plugin_id, BaseContainer *bc, void **data, Int *length );
	Bool						(*SavePreset)( Int32 db_index, const SDKBrowserURL &url, Int32 plugin_id, const BaseContainer *bc, void *data, Int length );
	Bool						(*DeletePreset)( Int32 db_index, const SDKBrowserURL &url, Int32 plugin_id );
	SDKBrowsePresets	*(*AllocPresetBrowser)( Int32 db_index );
	void						(*FreePresetBrowser)( SDKBrowsePresets *browse_presets );
	Bool						(*PresetBrowserGetNext)( SDKBrowsePresets *browse_presets, SDKBrowserURL &url, Int32 &plugin_id, Int &id );

	void						(*UpdateNotification)( SDKBrowserContentNodeRef node, Int32 flags );
	Int32						(*PreviewDialogMisc)( SubDialog *dlg, void *&private_data, Int32 cmd, Int32 value0, Int32 value1, void *value2, void *value3 );

	SDKBrowserContentNodeRef (*FindNode)( const SDKBrowserURL &url, Int32 flags, SDKBrowserContentNodeRef start_from  );

	Bool						(*RegisterBrowserPlugin)( SDKBrowserPluginRef plugin, UInt32 flags );
	Bool						(*UnregisterBrowserPlugin)( SDKBrowserPluginRef plugin );

	Bool 						(*Identify)( const SDKBrowserURL &url, UInt32 flags, SDKBrowserPluginRef *plugin_out );

	BaseList2D 			*(*GetDefaultObject)( Int32 id, UInt32 flags );
	Bool 						(*SetDefaultObject)( BaseList2D *bl, UInt32 flags );

	Bool						(*ReadNodesFromDatabase)( Int32 db_index, const SDKBrowserURL &base_url, SDKBrowserContentNodeRef base_node, SDKBrowser::InsertNodeFromDataBase *callback, void *user_data );

	Bool						(*GetPresetName)( Int32 db_index, const SDKBrowserURL &url, Int32 language_id, String &out_name );
	Bool						(*SetPresetName)( Int32 db_index, const SDKBrowserURL &url, Int32 language_id, const String &name );
	Bool						(*GetPresetAnnotation)( Int32 db_index, const SDKBrowserURL &url, String &annotation );
	Bool						(*SetPresetAnnotation)( Int32 db_index, const SDKBrowserURL &url, const String &annotation );
	Bool						(*SavePresetObject)( const SDKBrowserURL &url, BaseList2D *bl );
	Bool						(*ChangePresetURL)( Int32 db_index, const SDKBrowserURL &url, const SDKBrowserURL &new_url, Int32 plugin_id );
	Int32						(*GetDbIndex)( const SDKBrowserURL &url, UInt32 flags );
	Bool						(*CreatePresetNode)( Int32 db_index, const SDKBrowserURL &url, Int32 plugin_id, Int32 mode );

	BaseBitmap			*(*GetIconBaseBitmap)( SDKBrowserIcon* icon );
	Bool						(*SetPresetPreview)( Int32 db_index, const SDKBrowserURL &url,  Int32 mode, Int32 preview_quality, BaseBitmap *bm, const LocalFileTime *lft );

	Bool						(*MountPresetLibrary)( const Filename &fn, UInt32 flags, SDKBrowserURL *domain );
	Bool						(*CopyPreset)( const SDKBrowserURL &src, const SDKBrowserURL &dst );
	Bool						(*SetSortOrder)( Int32 mode, SDKBrowserContentNodeRef *nodes, Int32 cnt, void *reserved );
	Bool						(*ExistsPreset)( const SDKBrowserURL &url );

	BaseBitmap			*(*GetPresetPreview)( Int32 db_index, const SDKBrowserURL &url, Int32 frame_idx );
	Bool						(*GetPresetAnimationData)( Int32 db_index, const SDKBrowserURL &url, Int32 *first_frame_idx, Int32 *last_frame_idx, Float *fps );
	Bool						(*SetPresetAnimationData)( Int32 db_index, const SDKBrowserURL &url, Int32 first_frame_idx, Int32 last_frame_idx, Float fps );

	Bool						(*OpenNewBrowserWithTitle)( const SDKBrowserURL &path, const String& custom_title, UInt32 flags );
	void						*reserved[64 - 41];	// reserved pointers
};

//////////////////////////////////////////////////////////////////////////

struct BrowserURLMethods
{
	void			(*Init)( void *priv );
	void			(*Flush)( void *priv );
	void			(*Copy)( void *priv, void *src );
	void			(*AddString)( void *priv, const String &src );
	void			(*SetFilename)( void *priv, const Filename &src );
	void			(*SetString)( void *priv, const String &src );
	Bool			(BrowserURL::*GetFilename)( Filename &f ) const;
	void			(BrowserURL::*GetString)( String &s ) const;
	void			(BrowserURL::*GetDirectory)( BrowserURL &priv ) const;
	String		(BrowserURL::*GetFileString)( void ) const;
	Bool			(BrowserURL::*IsFilename)( void ) const;
	Bool			(BrowserURL::*CheckSuffix)( const String &s ) const;
	String		(BrowserURL::*GetSuffix)( void ) const;
	Bool			(BrowserURL::*Content)( void ) const;

	void		*reserved[(32 - 14)];	// reserved pointers
};

//////////////////////////////////////////////////////////////////////////

struct ReferenceObjectMethods
{
	void	(ReferenceObject::*add_reference)( void );
	void	(ReferenceObject::*remove_reference)( void );
	void	*reserved[6 * C4DPL_MEMBERMULTIPLIER];	// reserved ptmf entries
};

//////////////////////////////////////////////////////////////////////////

struct RTreeNodeMethods
{
	SDKReferenceObjectPtr<RTreeNode>	(RTreeNode::*GetUp)( void ) const;
	SDKReferenceObjectPtr<RTreeNode>	(RTreeNode::*GetDown)( void ) const;
	SDKReferenceObjectPtr<RTreeNode>	(RTreeNode::*GetNext)( void ) const;
	SDKReferenceObjectPtr<RTreeNode>	(RTreeNode::*GetPred)( void ) const;

	void		(RTreeNode::*InsertUnder)( SDKReferenceObjectPtr<RTreeNode> parent );
	void		(RTreeNode::*Remove)( void );

	void		*reserved[10 * C4DPL_MEMBERMULTIPLIER];	// reserved ptmf entries
};


//////////////////////////////////////////////////////////////////////////

struct SDKBrowserContentNodeMethods
{
	Bool								(SDKBrowserContentNodeInfo::*Init)( void *node );
	void								(SDKBrowserContentNodeInfo::*Free)( void );
	Int32								(SDKBrowserContentNodeInfo::*GetTypeID)( void );
	SDKBrowserPluginRef	(SDKBrowserContentNodeInfo::*GetPlugin)( UInt32 flags );

	String							(SDKBrowserContentNodeInfo::*GetName)( void );
	Int32								(SDKBrowserContentNodeInfo::*GetNodeURL)( SDKBrowserURL &url, UInt32 flags ) const;
	Bool								(SDKBrowserContentNodeInfo::*GetNodeTime)( UInt32 mode, LocalFileTime *out );
	UInt32								(SDKBrowserContentNodeInfo::*GetNodeFlags)( Int64 *out_size );

	SDKBrowserIcon			*(SDKBrowserContentNodeInfo::*GetIcon)( Int32 flags, Int32 pref_wh );

	Int32								(SDKBrowserContentNodeInfo::*UpdateDirectory)( void );

	Int32								(SDKBrowserContentNodeInfo::*PrivateCall)( Int32 plugin_id, Int32 node_type, Int32 selector, void *data );

	Int32								(SDKBrowserContentNodeInfo::*Rename)( Int32 mode, const String &name );
	Int32								(SDKBrowserContentNodeInfo::*NewFolder)( Int32 mode, const String &name, SDKBrowserContentNodeRef *folder );
	Int32								(SDKBrowserContentNodeInfo::*MoveFrom)( SDKBrowserContentNodeRef new_child, Int32 mode, CopyMoveCallback *callback, void *private_data, BaseThread *thread );
	Int32								(SDKBrowserContentNodeInfo::*CopyFrom)( SDKBrowserContentNodeRef new_child, Int32 mode, const String *rename, CopyMoveCallback *callback, void *private_data, BaseThread *thread );
	Int32								(SDKBrowserContentNodeInfo::*Delete)( Int32 mode, CopyMoveCallback *callback, void *private_data, BaseThread *thread );

	String							(SDKBrowserContentNodeInfo::*GetTypeName)( Int32 mode ) const;

	void								*reserved[15 * C4DPL_MEMBERMULTIPLIER];	// reserved ptmf entries
};

//////////////////////////////////////////////////////////////////////////

struct BrowserContentNodeMethods
{
	SDKBrowserContentNodeRef			(*Alloc)( SDKBrowserContentNodeInfo *node_info, SDKBrowserContentNodeMethods *node_ptmf );
	SDKBrowserContentNodeRef			(*AllocCategoryNode)( const String &name, const String &local_path, const Filename &icon_file );
	void													(*FreeNodes)( Int32 plugin_id );

	SDKBrowserContentNodeInfo			*(*GetNodeInfo)( const SDKBrowserContentNode *node, Int32 plugin_id );

	Int32													(BrowserContentNode::*GetTypeID)( void ) const;
	SDKBrowserPluginRef						(BrowserContentNode::*GetPlugin)( UInt32 flags ) const;

	String												(BrowserContentNode::*GetName)( void ) const;
	Int32													(BrowserContentNode::*GetNodeURL)( BrowserURL &url, UInt32 flags ) const;
	Bool													(BrowserContentNode::*GetNodeTime)( UInt32 mode, LocalFileTime *out ) const;
	UInt32													(BrowserContentNode::*GetNodeFlags)( Int64 *out_size ) const;

	SDKBrowserIcon								*(BrowserContentNode::*GetIcon)( Int32 flags, Int32 pref_wh ) const;

	Int32													(BrowserContentNode::*UpdateDirectory)( void ) const;
	Int32													(BrowserContentNode::*PrivateCall)( Int32 plugin_id, Int32 node_type, Int32 selector, void *data );	// Hook for private calls

	Int32													(BrowserContentNode::*Rename)( Int32 mode, const String &name );
	Int32													(BrowserContentNode::*NewFolder)( Int32 mode, const String &name, SDKBrowserContentNodeRef *folder );
	Int32													(BrowserContentNode::*MoveFrom)( SDKBrowserContentNodeRef new_child, Int32 mode, CopyMoveCallback *callback, void *private_data, BaseThread *thread );
	Int32													(BrowserContentNode::*CopyFrom)( SDKBrowserContentNodeRef new_child, Int32 mode, const String *rename, CopyMoveCallback *callback, void *private_data, BaseThread *thread );
	Int32													(BrowserContentNode::*Delete)( Int32 mode, CopyMoveCallback *callback, void *private_data, BaseThread *thread );

	String												(BrowserContentNode::*GetTypeName)( Int32 mode ) const;

	void													*reserved[13 * C4DPL_MEMBERMULTIPLIER];	// reserved ptmf entries
};

//////////////////////////////////////////////////////////////////////////

struct SDKBrowserPluginInterfaceMethods
{
	Int32									(SDKBrowserPluginInterfaceInfo::*GetPluginID)( String *plugin_name );
	Bool									(SDKBrowserPluginInterfaceInfo::*Identify)( const SDKBrowserURL &url, UChar *probe, Int32 size, UInt32 flags );
	String								(SDKBrowserPluginInterfaceInfo::*GetTypeName)( const SDKBrowserContentNodeRef node, const SDKBrowserURL *url, Int32 mode );
	String								*(SDKBrowserPluginInterfaceInfo::*GetTypeNames)( Int32 mode, Int32 *no_strings );

	SDKBrowserPreviewData	*(SDKBrowserPluginInterfaceInfo::*OpenPreviewBitmap)( BaseThread *thread, const SDKBrowserContentNodeRef node, const SDKBrowserURL *url, SDKBrowserPreviewInfo *info );
	void									(SDKBrowserPluginInterfaceInfo::*ClosePreviewBitmap)( SDKBrowserPreviewData *data );
	BaseBitmap						*(SDKBrowserPluginInterfaceInfo::*GetPreviewBitmap)( SDKBrowserPreviewData *data, Int32 w, Int32 h, Int32 quality );

	SDKBrowserIcon				*(SDKBrowserPluginInterfaceInfo::*GetIcon)( const SDKBrowserURL &url, Int32 pref_wh );

	SubDialog							*(SDKBrowserPluginInterfaceInfo::*OpenPreviewDialog)( SDKBrowserContentNodeRef node, Int32 tab_id );
	Int32									(SDKBrowserPluginInterfaceInfo::*ClosePreviewDialog)( SDKBrowserContentNodeRef node, SubDialog *s );
	Bool									(SDKBrowserPluginInterfaceInfo::*Open)( SDKBrowserContentNodeRef node, const SDKBrowserURL *url, Int32 flags );
	Int32									(SDKBrowserPluginInterfaceInfo::*UpdatePreviewDialog)( SDKBrowserContentNodeRef node, SubDialog *s );

	void									*reserved[20 * C4DPL_MEMBERMULTIPLIER];	// reserved ptmf entries
};

//////////////////////////////////////////////////////////////////////////

struct BrowserPluginInterfaceMethods
{
	SDKBrowserPluginRef			(*Alloc)( SDKBrowserPluginInterfaceInfo *plugin_info, SDKBrowserPluginInterfaceMethods *plugin_ptmf );
	void										(*Free)( SDKBrowserPluginRef plugin );

	Int32										(BrowserPluginInterface::*GetPluginID)( String *plugin_name );

	Bool										(BrowserPluginInterface::*Identify)( const SDKBrowserURL &url, UChar *probe, Int32 size, UInt32 flags );
	String									(BrowserPluginInterface::*GetTypeName)( const SDKBrowserContentNodeRef node, const SDKBrowserURL *url, Int32 mode );
	String									*(BrowserPluginInterface::*GetTypeNames)( Int32 mode, Int32 *no_strings );

	SDKBrowserPreviewData		*(BrowserPluginInterface::*OpenPreviewBitmap)( BaseThread *thread, const SDKBrowserContentNodeRef node, const SDKBrowserURL *url, SDKBrowserPreviewInfo *info );
	void										(BrowserPluginInterface::*ClosePreviewBitmap)( SDKBrowserPreviewData *data );
	BaseBitmap							*(BrowserPluginInterface::*GetPreviewBitmap)( SDKBrowserPreviewData *data, Int32 w, Int32 h, Int32 quality );

	SDKBrowserIcon					*(BrowserPluginInterface::*GetIcon)( const SDKBrowserURL &url, Int32 pref_wh );

	SubDialog								*(BrowserPluginInterface::*OpenPreviewDialog)( SDKBrowserContentNodeRef content, Int32 tab_id );
	Int32										(BrowserPluginInterface::*ClosePreviewDialog)( SDKBrowserContentNodeRef content, SubDialog *s );
	Bool										(BrowserPluginInterface::*Open)( SDKBrowserContentNodeRef content, const SDKBrowserURL *url, Int32 flags );
	Int32										(BrowserPluginInterface::*UpdatePreviewDialog)( SDKBrowserContentNodeRef node, SubDialog *s );

	void										*reserved[18 * C4DPL_MEMBERMULTIPLIER];	// reserved ptmf entries
};

//////////////////////////////////////////////////////////////////////////

struct BrowserLib : public C4DLibrary
{
	ReferenceObjectMethods	reference_object;
	BrowserMethods		*browser;
	BrowserURLMethods	*browser_url;
	RTreeNodeMethods	*rtree_node;
	BrowserContentNodeMethods	*content_node;
	BrowserPluginInterfaceMethods	*plugin_itf;
};

// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF
// INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF -- INTERNAL STUFF

#endif	// _LIB_BROWSER_H_
