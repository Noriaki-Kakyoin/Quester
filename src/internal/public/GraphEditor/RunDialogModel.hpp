#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QLabel>

#include <public/GraphEditor/ExecData.hpp>
#include <public/GraphEditor/DialogueData.hpp>

#include <public/dialogueselectornode.h>

#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;
using QtNodes::NodeValidationState;

namespace GraphEditor {
    /*!
    ### Model used to display a dialogue message on a quest or *on the fly*
    Needs a generated UE4 Character Database before usage.
    */
    class RunDialogModel : public NodeDataModel
    {
      Q_OBJECT

    public:
      RunDialogModel();

      virtual
      ~RunDialogModel() {}

    public:

    public:
      QString
      caption() const override
      {
        return QString("Run Dialogue");
      }

      QString
      portCaption(PortType portType, PortIndex portIndex) const override;

      bool
      portCaptionVisible(PortType portType, PortIndex portIndex) const override {
          return true;
      }

      QString
      name() const override
      {
        return QString("Run Dialogue");
      }

    public:

      QJsonObject
      save() const override
      {
        QJsonObject modelJson;

        modelJson["name"] = name();

        return modelJson;
      }

    public:

      bool
      hasDynamicPorts(PortType portType) const override;

      unsigned int
      nPorts(PortType portType) const override;

      NodeDataType
      dataType(PortType portType, PortIndex portIndex) const override;

      std::shared_ptr<NodeData>
      outData(PortIndex port) override;

      void
      setInData(std::shared_ptr<NodeData> data, PortIndex portIndex) override;

      QWidget *
      embeddedWidget() override { return _dialogue_selector_node; }

      NodeValidationState
      validationState() const override;

      QString
      validationMessage() const override;

      void
      compute(int dialogueSize);

      void
      restore(const QJsonObject& obj) override;

    private:
        std::vector<QType::DialogueNodeData> _numberList;
        DialogueSelectorNode * _dialogue_selector_node;

        NodeValidationState _modelValidationState = NodeValidationState::Warning;
        QString _modelValidationError = QString("Missing or incorrect inputs");
    };
}
