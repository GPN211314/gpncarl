#include<gtk/gtk.h>
#include<string.h>
#include "add_wubi.h"
void add_words(GtkWidget * widget,gpointer data)
{
  const char* word;
  char text[40]; 
  word=gtk_entry_get_text(GTK_ENTRY(data));
  if(strlen(word)<=3)
    gtk_entry_set_text(GTK_ENTRY(data),"至少输两个字");
  else
  {
    if(add_wubi(word,text)==1)
    {
      gtk_entry_set_text(GTK_ENTRY(data),"未查询到编码");
      return;
    }

    gtk_entry_set_text(GTK_ENTRY(data),(const char *)text);
  }
  return;
}
void delete_words(GtkWidget * Widget,gpointer data)
{
  const char * word;
  word=gtk_entry_get_text(GTK_ENTRY(data));
  if(strlen(word)<=3)
  {
    gtk_entry_set_text(GTK_ENTRY(data),"至少输两个字");
    return; 
  }
  if(delete_wubi(word)==0)
  {
    gtk_entry_set_text(GTK_ENTRY(data),"还没有这个词");
    return;
    
    
  }
  

  gtk_entry_set_text(GTK_ENTRY(data),"已删除这个词");
  return;


}
int main(int argc, char * argv[])
{
  
  GtkWidget * window;
  GtkWidget * main_box;
  GtkWidget * button;
  GtkWidget * entry;
  
  GtkWidget * button_box;
  GtkWidget * label_entry_box;
  GtkWidget * label;

  gtk_init (&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window),"Rime五笔造词、删词、反查");
  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  gtk_container_set_border_width(GTK_CONTAINER(window),15);
  g_signal_connect(G_OBJECT(window),"delete_event",G_CALLBACK(gtk_main_quit),NULL);
  gtk_widget_set_size_request(window,400,150);
  
  main_box=gtk_vbox_new(FALSE,10);
  gtk_container_add(GTK_CONTAINER(window),main_box);

  entry=gtk_entry_new();
  
  button=gtk_button_new_with_label("确定");
  
  button_box=gtk_hbox_new(FALSE,0);
  label_entry_box=gtk_hbox_new(FALSE,0);

  label=gtk_label_new(" 词组:      ");

  gtk_box_pack_start(GTK_BOX(main_box),label_entry_box,TRUE,TRUE,5);
  gtk_box_pack_end(GTK_BOX(main_box),button_box,TRUE,TRUE,5);
  gtk_box_pack_start(GTK_BOX(label_entry_box),label,FALSE,FALSE,0);
  gtk_box_pack_start(GTK_BOX(label_entry_box),entry,FALSE,FALSE,0);

  gtk_widget_set_size_request(GTK_WIDGET(entry),300,32);
  gtk_widget_set_size_request(GTK_WIDGET(button),100,10);

  gtk_box_pack_end(GTK_BOX(button_box),button,FALSE,FALSE,5);
  g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(add_words),entry);
  g_signal_connect(G_OBJECT(entry),"activate",G_CALLBACK(add_words),entry);

  gtk_widget_show(button);


  button=gtk_button_new_with_label("删除");
  gtk_widget_set_size_request(GTK_WIDGET(button),100,10);

  gtk_box_pack_start(GTK_BOX(button_box),button,FALSE,FALSE,5);
  g_signal_connect(G_OBJECT(button),"clicked",G_CALLBACK(delete_words),entry);

  gtk_widget_show(button);

  gtk_widget_show(button_box);
  gtk_widget_show(label);
  gtk_widget_show(label_entry_box);
  gtk_widget_show(entry);
  gtk_widget_show(main_box);
  gtk_widget_show(window);






  gtk_main();
  return 0;
}

