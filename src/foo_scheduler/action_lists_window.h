#pragma once

#include "action.h"
#include "action_list.h"

class PrefPageModel;

typedef CWinTraits<WS_CHILD | WS_VISIBLE |
	TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS, 0>	ActionListsWindowTraits;

class ActionListsWindow :
	public CWindowImpl<ActionListsWindow, CTreeViewCtrlEx, ActionListsWindowTraits>,
	public boost::signals2::trackable
{
public:
	void Init(PrefPageModel* pModel);

private:
	void AddActionList(ActionList* pActionList, HTREEITEM hInsertAfter);
	void AddAction(CTreeItem tiActionList, IAction* pAction);

	void ShowItemContextMenu(CTreeItem ti, const CPoint& point);
	void ShowActionListContextMenu(CTreeItem ti, const CPoint& pntScreen);
	void ShowActionContextMenu(CTreeItem ti, const CPoint& pntScreen);

	void AppendActionListItems(CMenu& menuPopup);
	void AppendActionsPopupMenu(CMenu& menuPopup, const std::vector<IAction*>& actionPrototypes);

	CTreeItem FindActionListItem(ActionList* pActionList);
	CTreeItem FindActionItem(ActionList* pActionList, IAction* pAction);

	void SwapTreeItems(CTreeItem ti1, CTreeItem ti2);

	ActionList* GetParentActionList(const CTreeItem& tiAction);

private:
	void OnActionListAdded(ActionList* pActionList);
	void OnActionListRemoved(ActionList* pActionList);
	void OnActionListUpdated(ActionList* pActionList);

	void OnActionAdded(ActionList* pActionList, IAction* pAction);
	void OnActionUpdated(ActionList* pActionList, IAction* pAction);
	void OnActionRemoved(ActionList* pActionList, IAction* pAction);

	void OnModelReset();

private:
	enum EItemType
	{
		itemTypeActionList, itemTypeAction
	};

	enum EActionListPopupMenuItems
	{
		actionListMenuItemEdit = 1000,
		actionListMenuItemDuplicate,
		actionListMenuItemRemove
	};

	enum EActionPopupMenuItems
	{
		actionMenuItemEdit = 1,
		actionMenuItemRemove,
		actionMenuItemMoveUp,
		actionMenuItemMoveDown
	};

	struct ItemData
	{
		EItemType itemType;
		void* pObj;

		ItemData(EItemType _itemType, void* _pObj) : itemType(_itemType), pObj(_pObj) {}
	};

private:
	BEGIN_MSG_MAP(ActionListsWindow)
		REFLECTED_NOTIFY_CODE_HANDLER_EX(TVN_DELETEITEM, OnDeleteItem)

		MSG_WM_LBUTTONDBLCLK(OnLButtonDblClk)
		MSG_WM_RBUTTONDOWN(OnRButtonDown)
		MSG_WM_CONTEXTMENU(OnContextMenu)

		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	LRESULT OnDeleteItem(LPNMHDR pnmh);

	void OnLButtonDblClk(UINT nFlags, CPoint point);
	void OnRButtonDown(UINT nFlags, CPoint point);
	void OnContextMenu(CWindow wnd, CPoint point);

private:
	PrefPageModel* m_pModel;
};

