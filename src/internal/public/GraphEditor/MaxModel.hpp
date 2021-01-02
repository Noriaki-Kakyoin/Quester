#pragma once

#include <nodes/NodeDataModel>

#include <public/GraphEditor/DialogueData.hpp>
#include <public/GraphEditor/ExecData.hpp>
#include <public/dialogueselectornode.h>


#include <public/Globals.h>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

class MaxModel : public NodeDataModel
{
   Q_OBJECT

public:
  MaxModel();
  virtual ~MaxModel() {}

  unsigned int
  nPorts(PortType portType) const override;

  bool
  hasDynamicPorts(PortType portType) const override;

  NodeDataType
  dataType(PortType portType, PortIndex portIndex) const override;

  std::shared_ptr<NodeData>
  outData(PortIndex port) override;

  void
  setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override;

public:

  QString
  caption() const override;

  bool
  portCaptionVisible(PortType portType, PortIndex portIndex) const override;

  //QString
  //portCaption(PortType portType, PortIndex portIndex) const override;

  QString
  name() const override;

public:

  QWidget *
  embeddedWidget() override { return _dialogue_selector_node; }

  //NodeValidationState
  //validationState() const override;
  //
  //QString
  //validationMessage() const override;

private:

  void
  restore(const QJsonObject& obj) override;

  void
  compute();

private:
   DialogueSelectorNode * _dialogue_selector_node;

   std::vector<QType::DialogueNodeData> _numberList;
   std::shared_ptr<DialogueData> _result;

   //NodeValidationState _modelValidationState = NodeValidationState::Warning;
   //QString _modelValidationError = QString("Missing or incorrect inputs");
};
