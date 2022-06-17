#pragma once

#include <stddef.h>
#include <imgui.h>

#ifdef IMNODES_USER_CONFIG
#include IMNODES_USER_CONFIG
#endif

#ifndef IMNODES_NAMESPACE
#define IMNODES_NAMESPACE ImNodes
#endif

#if defined __cplusplus
    #define EXTERN extern "C"
#else
    #include <stdarg.h>
    #include <stdbool.h>
    #define EXTERN extern
#endif

typedef int ImNodesCol;             // -> enum ImNodesCol_
typedef int ImNodesStyleVar;        // -> enum ImNodesStyleVar_
typedef int ImNodesStyleFlags;      // -> enum ImNodesStyleFlags_
typedef int ImNodesPinShape;        // -> enum ImNodesPinShape_
typedef int ImNodesAttributeFlags;  // -> enum ImNodesAttributeFlags_
typedef int ImNodesMiniMapLocation; // -> enum ImNodesMiniMapLocation_

enum ImNodesCol_
{
    ImNodesCol_NodeBackground = 0,
    ImNodesCol_NodeBackgroundHovered,
    ImNodesCol_NodeBackgroundSelected,
    ImNodesCol_NodeOutline,
    ImNodesCol_TitleBar,
    ImNodesCol_TitleBarHovered,
    ImNodesCol_TitleBarSelected,
    ImNodesCol_Link,
    ImNodesCol_LinkHovered,
    ImNodesCol_LinkSelected,
    ImNodesCol_Pin,
    ImNodesCol_PinHovered,
    ImNodesCol_BoxSelector,
    ImNodesCol_BoxSelectorOutline,
    ImNodesCol_GridBackground,
    ImNodesCol_GridLine,
    ImNodesCol_GridLinePrimary,
    ImNodesCol_MiniMapBackground,
    ImNodesCol_MiniMapBackgroundHovered,
    ImNodesCol_MiniMapOutline,
    ImNodesCol_MiniMapOutlineHovered,
    ImNodesCol_MiniMapNodeBackground,
    ImNodesCol_MiniMapNodeBackgroundHovered,
    ImNodesCol_MiniMapNodeBackgroundSelected,
    ImNodesCol_MiniMapNodeOutline,
    ImNodesCol_MiniMapLink,
    ImNodesCol_MiniMapLinkSelected,
    ImNodesCol_MiniMapCanvas,
    ImNodesCol_MiniMapCanvasOutline,
    ImNodesCol_COUNT
};

enum ImNodesStyleVar_
{
    ImNodesStyleVar_GridSpacing = 0,
    ImNodesStyleVar_NodeCornerRounding,
    ImNodesStyleVar_NodePadding,
    ImNodesStyleVar_NodeBorderThickness,
    ImNodesStyleVar_LinkThickness,
    ImNodesStyleVar_LinkLineSegmentsPerLength,
    ImNodesStyleVar_LinkHoverDistance,
    ImNodesStyleVar_PinCircleRadius,
    ImNodesStyleVar_PinQuadSideLength,
    ImNodesStyleVar_PinTriangleSideLength,
    ImNodesStyleVar_PinLineThickness,
    ImNodesStyleVar_PinHoverRadius,
    ImNodesStyleVar_PinOffset,
    ImNodesStyleVar_MiniMapPadding,
    ImNodesStyleVar_MiniMapOffset,
    ImNodesStyleVar_COUNT
};

enum ImNodesStyleFlags_
{
    ImNodesStyleFlags_None = 0,
    ImNodesStyleFlags_NodeOutline = 1 << 0,
    ImNodesStyleFlags_GridLines = 1 << 2,
    ImNodesStyleFlags_GridLinesPrimary = 1 << 3,
    ImNodesStyleFlags_GridSnapping = 1 << 4
};

enum ImNodesPinShape_
{
    ImNodesPinShape_Circle,
    ImNodesPinShape_CircleFilled,
    ImNodesPinShape_Triangle,
    ImNodesPinShape_TriangleFilled,
    ImNodesPinShape_Quad,
    ImNodesPinShape_QuadFilled
};

// This enum controls the way the attribute pins behave.
enum ImNodesAttributeFlags_
{
    ImNodesAttributeFlags_None = 0,
    // Allow detaching a link by left-clicking and dragging the link at a pin it is connected to.
    // NOTE: the user has to actually delete the link for this to work. A deleted link can be
    // detected by calling IsLinkDestroyed() after EndNodeEditor().
    ImNodesAttributeFlags_EnableLinkDetachWithDragClick = 1 << 0,
    // Visual snapping of an in progress link will trigger IsLink Created/Destroyed events. Allows
    // for previewing the creation of a link while dragging it across attributes. See here for demo:
    // https://github.com/Nelarius/imnodes/issues/41#issuecomment-647132113 NOTE: the user has to
    // actually delete the link for this to work. A deleted link can be detected by calling
    // IsLinkDestroyed() after EndNodeEditor().
    ImNodesAttributeFlags_EnableLinkCreationOnSnap = 1 << 1
};

struct ImNodesIO
{
    struct EmulateThreeButtonMouse
    {
        #ifdef __cplusplus
        EmulateThreeButtonMouse();
        #endif

        // The keyboard modifier to use in combination with mouse left click to pan the editor view.
        // Set to NULL by default. To enable this feature, set the modifier to point to a boolean
        // indicating the state of a modifier. For example,
        //
        // ImNodes::GetIO().EmulateThreeButtonMouse.Modifier = &ImGui::GetIO().KeyAlt;
        const bool* Modifier;
    } EmulateThreeButtonMouse;

    struct LinkDetachWithModifierClick
    {
        #ifdef __cplusplus
        LinkDetachWithModifierClick();
        #endif

        // Pointer to a boolean value indicating when the desired modifier is pressed. Set to NULL
        // by default. To enable the feature, set the modifier to point to a boolean indicating the
        // state of a modifier. For example,
        //
        // ImNodes::GetIO().LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
        //
        // Left-clicking a link with this modifier pressed will detach that link. NOTE: the user has
        // to actually delete the link for this to work. A deleted link can be detected by calling
        // IsLinkDestroyed() after EndNodeEditor().
        const bool* Modifier;
    } LinkDetachWithModifierClick;

    struct MultipleSelectModifier
    {
        #ifdef __cplusplus
        MultipleSelectModifier();
        #endif

        // Pointer to a boolean value indicating when the desired modifier is pressed. Set to NULL
        // by default. To enable the feature, set the modifier to point to a boolean indicating the
        // state of a modifier. For example,
        //
        // ImNodes::GetIO().MultipleSelectModifier.Modifier = &ImGui::GetIO().KeyCtrl;
        //
        // Left-clicking a node with this modifier pressed will add the node to the list of
        // currently selected nodes. If this value is NULL, the Ctrl key will be used.
        const bool* Modifier;
    } MultipleSelectModifier;

    // Holding alt mouse button pans the node area, by default middle mouse button will be used
    // Set based on ImGuiMouseButton values
    int AltMouseButton;

    // Panning speed when dragging an element and mouse is outside the main editor view.
    float AutoPanningSpeed;

    #ifdef __cplusplus
    ImNodesIO();
    #endif
};
typedef struct ImNodesIO ImNodesIO;

struct ImNodesStyle
{
    float GridSpacing;

    float  NodeCornerRounding;
    ImVec2 NodePadding;
    float  NodeBorderThickness;

    float LinkThickness;
    float LinkLineSegmentsPerLength;
    float LinkHoverDistance;

    // The following variables control the look and behavior of the pins. The default size of each
    // pin shape is balanced to occupy approximately the same surface area on the screen.

    // The circle radius used when the pin shape is either ImNodesPinShape_Circle or
    // ImNodesPinShape_CircleFilled.
    float PinCircleRadius;
    // The quad side length used when the shape is either ImNodesPinShape_Quad or
    // ImNodesPinShape_QuadFilled.
    float PinQuadSideLength;
    // The equilateral triangle side length used when the pin shape is either
    // ImNodesPinShape_Triangle or ImNodesPinShape_TriangleFilled.
    float PinTriangleSideLength;
    // The thickness of the line used when the pin shape is not filled.
    float PinLineThickness;
    // The radius from the pin's center position inside of which it is detected as being hovered
    // over.
    float PinHoverRadius;
    // Offsets the pins' positions from the edge of the node to the outside of the node.
    float PinOffset;

    // Mini-map padding size between mini-map edge and mini-map content.
    ImVec2 MiniMapPadding;
    // Mini-map offset from the screen side.
    ImVec2 MiniMapOffset;

    // By default, ImNodesStyleFlags_NodeOutline and ImNodesStyleFlags_Gridlines are enabled.
    ImNodesStyleFlags Flags;
    // Set these mid-frame using Push/PopColorStyle. You can index this color array with with a
    // ImNodesCol value.
    unsigned int Colors[ImNodesCol_COUNT];

    #ifdef __cplusplus
    ImNodesStyle();
    #endif
};
typedef struct ImNodesStyle ImNodesStyle;

enum ImNodesMiniMapLocation_
{
    ImNodesMiniMapLocation_BottomLeft,
    ImNodesMiniMapLocation_BottomRight,
    ImNodesMiniMapLocation_TopLeft,
    ImNodesMiniMapLocation_TopRight,
};

struct ImGuiContext;
struct ImVec2;

typedef struct ImNodesContext ImNodesContext;

// An editor context corresponds to a set of nodes in a single workspace (created with a single
// Begin/EndNodeEditor pair)
//
// By default, the library creates an editor context behind the scenes, so using any of the imnodes
// functions doesn't require you to explicitly create a context.
typedef struct ImNodesEditorContext ImNodesEditorContext;

// Callback type used to specify special behavior when hovering a node in the minimap
#ifndef ImNodesMiniMapNodeHoveringCallback
typedef void (*ImNodesMiniMapNodeHoveringCallback)(int, void*);
#endif

#ifndef ImNodesMiniMapNodeHoveringCallbackUserData
typedef void* ImNodesMiniMapNodeHoveringCallbackUserData;
#endif

// namespace IMNODES_NAMESPACE
// {
// Call this function if you are compiling imnodes in to a dll, separate from ImGui. Calling this
// function sets the GImGui global variable, which is not shared across dll boundaries.
EXTERN void SetImGuiContext(ImGuiContext* ctx);

EXTERN ImNodesContext* CreateContext();
EXTERN void            DestroyContext(ImNodesContext* ctx); // NULL = destroy current context
EXTERN ImNodesContext* GetCurrentContext();
EXTERN void            SetCurrentContext(ImNodesContext* ctx);

EXTERN ImNodesEditorContext* EditorContextCreate();
EXTERN void                  EditorContextFree(ImNodesEditorContext*);
EXTERN void                  EditorContextSet(ImNodesEditorContext*);
EXTERN ImVec2                EditorContextGetPanning();
EXTERN void                  EditorContextResetPanning(const ImVec2 pos);
EXTERN void                  EditorContextMoveToNode(const int node_id);

EXTERN ImNodesIO* GetIO();

// Returns the global style struct. See the struct declaration for default values.
EXTERN ImNodesStyle* GetStyle();
// Style presets matching the dear imgui styles of the same name. If dest is NULL, the active
// context's ImNodesStyle instance will be used as the destination.
EXTERN void StyleColorsDark(ImNodesStyle* dest); // on by default
EXTERN void StyleColorsClassic(ImNodesStyle* dest);
EXTERN void StyleColorsLight(ImNodesStyle* dest);

// The top-level function call. Call this before calling BeginNode/EndNode. Calling this function
// will result the node editor grid workspace being rendered.
EXTERN void BeginNodeEditor();
EXTERN void EndNodeEditor();

// Add a navigable minimap to the editor; call before EndNodeEditor after all
// nodes and links have been specified
EXTERN void MiniMap(
    const float                                      minimap_size_fraction/* = 0.2f*/,
    const ImNodesMiniMapLocation                     location/* = ImNodesMiniMapLocation_TopLeft*/,
    const ImNodesMiniMapNodeHoveringCallback         node_hovering_callback/* = NULL*/,
    const ImNodesMiniMapNodeHoveringCallbackUserData node_hovering_callback_data/* = NULL*/);

// Use PushColorStyle and PopColorStyle to modify ImNodesStyle::Colors mid-frame.
EXTERN void PushColorStyle(ImNodesCol item, unsigned int color);
EXTERN void PopColorStyle();
EXTERN void PushStyleVar(ImNodesStyleVar style_item, float value);
EXTERN void PushStyleVar2(ImNodesStyleVar style_item, const ImVec2 value);
EXTERN void PopStyleVar(int count);

// id can be any positive or negative integer, but INT_MIN is currently reserved for internal use.
EXTERN void BeginNode(int id);
EXTERN void EndNode();

EXTERN ImVec2 GetNodeDimensions(int id);

// Place your node title bar content (such as the node title, using ImGui::Text) between the
// following function calls. These functions have to be called before adding any attributes, or the
// layout of the node will be incorrect.
EXTERN void BeginNodeTitleBar();
EXTERN void EndNodeTitleBar();

// Attributes are ImGui UI elements embedded within the node. Attributes can have pin shapes
// rendered next to them. Links are created between pins.
//
// The activity status of an attribute can be checked via the IsAttributeActive() and
// IsAnyAttributeActive() function calls. This is one easy way of checking for any changes made to
// an attribute's drag float UI, for instance.
//
// Each attribute id must be unique.

// Create an input attribute block. The pin is rendered on left side.
EXTERN void BeginInputAttribute(int id, ImNodesPinShape shape/* = ImNodesPinShape_CircleFilled*/);
EXTERN void EndInputAttribute();
// Create an output attribute block. The pin is rendered on the right side.
EXTERN void BeginOutputAttribute(int id, ImNodesPinShape shape/* = ImNodesPinShape_CircleFilled*/);
EXTERN void EndOutputAttribute();
// Create a static attribute block. A static attribute has no pin, and therefore can't be linked to
// anything. However, you can still use IsAttributeActive() and IsAnyAttributeActive() to check for
// attribute activity.
EXTERN void BeginStaticAttribute(int id);
EXTERN void EndStaticAttribute();

// Push a single AttributeFlags value. By default, only AttributeFlags_None is set.
EXTERN void PushAttributeFlag(ImNodesAttributeFlags flag);
EXTERN void PopAttributeFlag();

// Render a link between attributes.
// The attributes ids used here must match the ids used in Begin(Input|Output)Attribute function
// calls. The order of start_attr and end_attr doesn't make a difference for rendering the link.
EXTERN void Link(int id, int start_attribute_id, int end_attribute_id);

// Enable or disable the ability to click and drag a specific node.
EXTERN void SetNodeDraggable(int node_id, const bool draggable);

// The node's position can be expressed in three coordinate systems:
// * screen space coordinates, -- the origin is the upper left corner of the window.
// * editor space coordinates -- the origin is the upper left corner of the node editor window
// * grid space coordinates, -- the origin is the upper left corner of the node editor window,
// translated by the current editor panning vector (see EditorContextGetPanning() and
// EditorContextResetPanning())

// Use the following functions to get and set the node's coordinates in these coordinate systems.

EXTERN void SetNodeScreenSpacePos(int node_id, const ImVec2 screen_space_pos);
EXTERN void SetNodeEditorSpacePos(int node_id, const ImVec2 editor_space_pos);
EXTERN void SetNodeGridSpacePos(int node_id, const ImVec2 grid_pos);

EXTERN ImVec2 GetNodeScreenSpacePos(const int node_id);
EXTERN ImVec2 GetNodeEditorSpacePos(const int node_id);
EXTERN ImVec2 GetNodeGridSpacePos(const int node_id);

// If ImNodesStyleFlags_GridSnapping is enabled, snap the specified node's origin to the grid.
EXTERN void SnapNodeToGrid(int node_id);

// Returns true if the current node editor canvas is being hovered over by the mouse, and is not
// blocked by any other windows.
EXTERN bool IsEditorHovered();
// The following functions return true if a UI element is being hovered over by the mouse cursor.
// Assigns the id of the UI element being hovered over to the function argument. Use these functions
// after EndNodeEditor() has been called.
EXTERN bool IsNodeHovered(int* node_id);
EXTERN bool IsLinkHovered(int* link_id);
EXTERN bool IsPinHovered(int* attribute_id);

// Use The following two functions to query the number of selected nodes or links in the current
// editor. Use after calling EndNodeEditor().
EXTERN int NumSelectedNodes();
EXTERN int NumSelectedLinks();
// Get the selected node/link ids. The pointer argument should point to an integer array with at
// least as many elements as the respective NumSelectedNodes/NumSelectedLinks function call
// returned.
EXTERN void GetSelectedNodes(int* node_ids);
EXTERN void GetSelectedLinks(int* link_ids);
// Clears the list of selected nodes/links. Useful if you want to delete a selected node or link.
EXTERN void ClearNodesSelection();
EXTERN void ClearLinksSelection();
// Use the following functions to add or remove individual nodes or links from the current editors
// selection. Note that all functions require the id to be an existing valid id for this editor.
// Select-functions has the precondition that the object is currently considered unselected.
// Clear-functions has the precondition that the object is currently considered selected.
// Preconditions listed above can be checked via IsNodeSelected/IsLinkSelected if not already
// known.
EXTERN void SelectNode(int node_id);
EXTERN void ClearNodeSelection(int node_id);
EXTERN bool IsNodeSelected(int node_id);
EXTERN void SelectLink(int link_id);
EXTERN void ClearLinkSelection(int link_id);
EXTERN bool IsLinkSelected(int link_id);

// Was the previous attribute active? This will continuously return true while the left mouse button
// is being pressed over the UI content of the attribute.
EXTERN bool IsAttributeActive();
// Was any attribute active? If so, sets the active attribute id to the output function argument.
EXTERN bool IsAnyAttributeActive(int* attribute_id/* = NULL*/);

// Use the following functions to query a change of state for an existing link, or new link. Call
// these after EndNodeEditor().

// Did the user start dragging a new link from a pin?
EXTERN bool IsLinkStarted(int* started_at_attribute_id);
// Did the user drop the dragged link before attaching it to a pin?
// There are two different kinds of situations to consider when handling this event:
// 1) a link which is created at a pin and then dropped
// 2) an existing link which is detached from a pin and then dropped
// Use the including_detached_links flag to control whether this function triggers when the user
// detaches a link and drops it.
EXTERN bool IsLinkDropped(int* started_at_attribute_id/* = NULL*/, bool including_detached_links/* = true*/);
// Did the user finish creating a new link?
EXTERN bool IsLinkCreated(
    int*  started_at_attribute_id,
    int*  ended_at_attribute_id,
    bool* created_from_snap/* = NULL*/);
EXTERN bool IsNodeLinkCreated(
    int*  started_at_node_id,
    int*  started_at_attribute_id,
    int*  ended_at_node_id,
    int*  ended_at_attribute_id,
    bool* created_from_snap/*= NULL*/);

// Was an existing link detached from a pin by the user? The detached link's id is assigned to the
// output argument link_id.
EXTERN bool IsLinkDestroyed(int* link_id);

// Use the following functions to write the editor context's state to a string, or directly to a
// file. The editor context is serialized in the INI file format.

// const char* SaveCurrentEditorStateToIniString(size_t* const data_size/* = NULL*/);
// EXTERN const char* SaveEditorStateToIniString(const ImNodesEditorContext* const editor_ptr, size_t* const data_size/* = NULL*/);

// EXTERN void LoadCurrentEditorStateFromIniString(const char* data, size_t data_size);
// EXTERN void LoadEditorStateFromIniString(const ImNodesEditorContext* const editor_ptr, const char* const data, const size_t data_size);

// EXTERN void SaveCurrentEditorStateToIniFile(const char* const file_name);
// EXTERN void SaveEditorStateToIniFile(const ImNodesEditorContext* const editor, const char* file_name);

// EXTERN void LoadCurrentEditorStateFromIniFile(const char* const file_name);
// EXTERN void LoadEditorStateFromIniFile(ImNodesEditorContext* editor, const char* file_name);
// } // namespace IMNODES_NAMESPACE
