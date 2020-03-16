#include <gtk/gtk.h>

static void hello(GtkWidget *widget, gpointer data) {
    g_print("Hello World\n");
}

static void destroy(GtkWidget *widget, gpointer data) { gtk_main_quit(); }

static gboolean delete_event(GtkWidget *widget, GdkEvent *event,
                             gpointer data) {
    /* 若此函数在“delete-event”处理函数(signal handler)中返回值为FALSE，则GTK会发出"detroy"信号。
     * 若返回值为TRUE，则窗口不会被销毁(destroy)。
     * 这个机制对于弹出“你确定要关闭窗口吗？”的提示非常有用。
     */
    g_print("delete event occurred\n");
    /* Change TRUE to FALSE and the main window will be destroyed with
     * a "delete-event". */

    return FALSE;
}

int main(int argc, char *argv[]) {
    /* GtkWidget是用来存放控件的变量类型*/
    GtkWidget *window;
    GtkWidget *button;

    /* gtk_init在所有GTK程序中都会被调用。这里主要是负责解析来自命令行的参数。*/
    gtk_init(&argc, &argv);

    /* create a new window */
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    /* 当窗口得到"delete-event"信号时(通常是用户按下了关闭按钮或者是关闭选项)，
     * 会调用我们定义的delete_event()函数。向回调函数(callback function)传递的值是NULL，
     * 会被回调函数忽略掉。
     */
    g_signal_connect(window, "delete-event", G_CALLBACK(delete_event), NULL);

    /* 将"destroy"事件连接到一个处理函数。
     * “destroy”事件通常会在以下情况时被触发：
     * 1. 调用gtk_widget_destroy()函数;
     * 2. "delete-event"回调函数返回值为FALSE;
     */
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    /* Sets the border width of the window. */
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    /* 创建一个新按钮，并设定标签为 "Hello World" */
    button = gtk_button_new_with_label("Hello World");

    /* 当按钮接受到“clicked”信号时，它就会调用G_CALLBACK内指定的函数。*/
    g_signal_connect(button, "clicked", G_CALLBACK(hello), NULL);

    /* This will cause the window to be destroyed by calling
     * gtk_widget_destroy(window) when "clicked".  Again, the destroy
     * signal could come from here, or the window manager. */
    // g_signal_connect_swapped(button, "clicked",
    // G_CALLBACK(gtk_widget_destroy),
    //                             window);

    /* This packs the button into the window (a gtk container). */
    gtk_container_add(GTK_CONTAINER(window), button);

    /* The final step is to display this newly created widget. */
    gtk_widget_show(button);

    /* and the window */
    gtk_widget_show(window);

    /* All GTK applications must have a gtk_main(). Control ends here
     * and waits for an event to occur (like a key press or
     * mouse event). */
    gtk_main();

    return 0;
}
