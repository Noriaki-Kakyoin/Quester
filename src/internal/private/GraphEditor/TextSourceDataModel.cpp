#include <public/GraphEditor/TextSourceDataModel.hpp>

TextSourceDataModel::
TextSourceDataModel()
  : _textEdit(new QTextEdit("Default Text"))
{
  _textEdit->setStyleSheet("margin: 10px;background:transparent;border:3px solid yellow;border-radius: 10px;");
  connect(_textEdit, SIGNAL(textChanged()), this, SLOT(onTextEdited()));
}


unsigned int
TextSourceDataModel::
nPorts(PortType portType) const
{
  unsigned int result = 1;

  switch (portType)
  {
    case PortType::In:
      result = 0;
      break;

    case PortType::Out:
      result = 1;

    default:
      break;
  }

  return result;
}


void
TextSourceDataModel::
onTextEdited()
{
  //QSize size = _textEdit->document()->size().toSize();
  //_textEdit->setFixedHeight( size.height() + 3 );
  //Q_UNUSED(string);

  Q_EMIT dataUpdated(0);
}


NodeDataType
TextSourceDataModel::
dataType(PortType, PortIndex) const
{
  return TextData().type();
}


std::shared_ptr<NodeData>
TextSourceDataModel::
outData(PortIndex)
{
  return std::make_shared<TextData>(_textEdit->toPlainText());
}