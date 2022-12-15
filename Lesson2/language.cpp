#include "language.h"
#include "ui_language.h"

language::language(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::language)
{
    ui->setupUi(this);
    QStringList strl;
    strl << "С++" << "Python" <<  "Java" << "C#"  << "PHP" << "JavaScript";
    model = new QStandardItemModel(strl.size(), 1, this);
    for (int i = 0; i < model->rowCount() ; ++i)
    {
        QModelIndex index = model->index(i,0);
        QString str = strl[i];
        model->setData(index, str, Qt::DisplayRole);
        model->setData(index, "ToolTip fr" + str, Qt::ToolTipRole);
        model->setData(index, QIcon("./icons/" + str +".png"), Qt::DecorationRole);
    }
    ui->listWidget->addItems(strl);
    ui->listWidget->setViewMode(QListView::IconMode);
    ui->listWidget->setDragDropMode(QAbstractItemView::InternalMove);
}

language::~language()
{
    delete ui;
}
/*
 *2. Создать список с названиями языков программирования (С++, Python, Java, C#, PHP, JavaScript).
 * Для каждого элемента списка рядом отобразить иконку с логотипом языка программирования.
 *   Иконку для него поставить любую (по-умолчанию).
 *   Создать CheckBox и когда будет стоять галочка, отобразить список в режиме иконок (нужен метод setViewMode()).
 *   Когда галочка не стоит, то список должен отображаться в обычном режиме. Подсказка: используйте справку qt, вызов F1.
 */

void language::on_addBut_clicked()
{
    QString str = "Новый язык программирования";
    ui->listWidget->addItem(str);
}


void language::on_delButton_clicked()
{
    QListWidgetItem *item = ui->listWidget->item(ui->listWidget->currentRow());
     if (!item)
     {
      QMessageBox::information(this,tr("Ошибка"),tr("Не выбран элемент в списке"));
      return;
     }
     ui->listWidget->takeItem (ui->listWidget->currentRow());
}

void language::on_listWidget_doubleClicked(const QModelIndex &index)
{
    Q_UNUSED(index)
    QListWidgetItem *item = ui->listWidget->currentItem();
    item->setFlags (item->flags () | Qt::ItemIsEditable);
}


void language::on_checkBox_clicked(bool checked)
{
    if (!checked)
    {
        ui->listWidget->setViewMode(QListView::ListMode);
    }
}

