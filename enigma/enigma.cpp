#include "enigma.h"
#include <ui_enigma.h>
#include <qimage.h>
#include <qmessagebox.h>
#include <qfiledialog.h>

enigma::enigma(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//�ź�������� begin
	connect(ui.btnEncodeChooseAddress, SIGNAL(clicked()), this, SLOT(clickBtnEncodeChooseAddress()));
	connect(ui.rbtnEncodeSaveSide, SIGNAL(clicked()), this, SLOT(clickRbtnEncodeSaveSide()));
	connect(ui.rbtnEncodeChoose, SIGNAL(clicked()), this, SLOT(clickRbtnEncodeChoose()));
	connect(ui.btnEncode, SIGNAL(clicked()), this, SLOT(clickBtnEncode()));
	//�ź�������� end
}

enigma::~enigma()
{
}

void enigma::clickBtnEncodeChooseAddress()//ѡ��Ҫ�����txt���ļ��и�·��
{
	QString getPath = QFileDialog::getExistingDirectory(this);
	if (!getPath.isNull())
	{
		ui.lineTxtNowAddress->setText(getPath);
	}
}

void enigma::clickRbtnEncodeSaveSide()//ѡ�񱣴�ͼƬ���ı���
{
	ui.lineEncodeSaveNowAddress->setEnabled(false);
}

void enigma::clickRbtnEncodeChoose()//ѡ�񱣴��ͼƬ·��
{
	ui.lineEncodeSaveNowAddress->setEnabled(true);
	QString getPath = QFileDialog::getExistingDirectory(this);
	if (!getPath.isNull())
	{
		ui.lineEncodeSaveNowAddress->setText(getPath);
	}
}

void enigma::clickBtnEncode()//��ʼ����
{
	QDir txtPath(ui.lineTxtNowAddress->text()),savePath(ui.lineEncodeSaveNowAddress->text());
	if (!txtPath.exists())//�ж���Ҫ����ĸ��ļ����Ƿ����
	{
		ui.lblEncodeState->setStyleSheet("color:red;");
		ui.lblEncodeState->setText(QStringLiteral("��Ҫ����ĸ��ļ��в�����"));
		return;
	}
	if (ui.rbtnEncodeChoose->isChecked())
	{//�����浽ͬһ·���£����Ƿ���ڻ��ܷ񴴽�
		if (!savePath.exists() && !savePath.mkdir(ui.lineEncodeSaveNowAddress->text()))
		{
			ui.lblEncodeState->setStyleSheet("color:red;");
			ui.lblEncodeState->setText(QStringLiteral("�����ַ�����ڲ��Ҵ���ʧ��"));
			return;
		}
	}
	//��ʼ����
	ui.chkEncodeDebug->setEnabled(false);
	ui.btnEncode->setEnabled(false);
	ui.lblEncodeState->setStyleSheet("color:black;");
	ui.lblEncodeState->setText(QStringLiteral("������..."));
	count = 0;
	QStringList allTxtPath = getAllFilePath(true,ui.lineTxtNowAddress->text());
	
	//��������

}

QStringList enigma::getAllFilePath(bool isTxt,QString path)//��ȡ�����ļ�·��
{
	QStringList filters;
	if (isTxt)//�ļ�����
	{
		filters << QString("*.txt");
	}
	else
	{
		filters << QString("*.bmp");
	}
	QDirIterator dirIterator(path,
		filters,
		QDir::Files | QDir::NoSymLinks,
		QDirIterator::Subdirectories);
	QStringList stringList;
	while (dirIterator.hasNext())
	{
		dirIterator.next();
		QFileInfo fileInfo = dirIterator.fileInfo();
		QString absoluteFilePath = fileInfo.absoluteFilePath();
		stringList.append(absoluteFilePath);
	}
	return stringList;

}
