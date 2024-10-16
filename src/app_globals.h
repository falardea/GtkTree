/**
 * @brief A place for globals
 */
#ifndef APP_GLOBALS_H__
#define APP_GLOBALS_H__
#include <gtk/gtk.h>

#define DEFAULT_TIMESTAMP_LOG_FORMAT "%04d-%02d-%02dT%02d:%02d:%02d"

typedef enum {
   RVALUE_SUCCESS,
   RVALUE_ERROR
} RVALUE;

typedef enum {
   LOGLEVEL_DEBUG,
   LOGLEVEL_INFO,
   LOGLEVEL_ERROR
} LOGLEVEL;

extern const char* DEBUG_STR;
extern const char* INFO_STR;
extern const char* ERROR_STR;
extern const int   LOGGING_MAX_MSG_LENGTH;

typedef struct {
   GtkWidget   *w_msg_out_textview;
   GtkWidget   *w_say_something_entry;
   GtkWidget   *w_do_something_button;
   GtkWidget   *w_home_page_overlay;

   GtkWidget   *w_basic_items_combo;
   GtkWidget   *w_timestamp_selection_combobox;

   GtkWidget   *w_brand_logo;

   GtkWidget   *w_model_viewers;
   GtkWidget   *w_samples_page;
   GtkWidget   *w_tree_explorer;
   GtkWidget   *w_tree_branch_view;
   GtkWidget   *w_tree_leaf_view;
   GtkWidget   *w_empty_viewer;
   GObject     *g_trslctnSelectedTreeBranch;

   GtkWidget   *w_listbox_row_container;
   GtkWidget   *w_listbox_item_1;
   GtkWidget   *w_listbox_item_2;

   GtkWidget   *w_trvwSamplesTable;
   GObject     *g_trslctnSelectedSample;



   GtkWidget   *w_tbtnEditSelection;
   GtkWidget   *w_tbtnCreateRow;
   GtkWidget   *w_tbtnDeleteRow;
   GtkWidget   *w_ppvrAreYouSure;
   GtkWidget   *w_lblPopoverAreYouSureMsg;
   GtkWidget   *w_btnAreYouSureConfirm;
   GtkWidget   *w_btnAreYouSureCancel;

   GtkWidget   *w_editSampleDateTime;
   GtkWidget   *w_lblSampleDate;
   GtkWidget   *w_entrySampleHour;
   GtkWidget   *w_entrySampleMinute;
   // Popover Datepicker
   GtkWidget   *w_ppvrDatepicker;
   GtkWidget   *w_popCalendar;
   GtkWidget   *w_popDone;
   GtkWidget   *w_popCancel;

   GtkWidget   *w_entryMeasurement1;
   GtkWidget   *w_entryMeasurement2;
   GtkWidget   *w_entryMeasurement3;
   GtkWidget   *w_entryMeasurement4;

   GtkWidget   *w_entryCalculationA;
   GtkWidget   *w_entryCalculationB;

   GtkWidget   *w_btnChangeRow;
   GtkWidget   *w_btnCancelRowChange;


} app_widget_ref_struct;

extern app_widget_ref_struct *g_app_widget_refs;

#endif  /* APP_GLOBALS_H__ */
