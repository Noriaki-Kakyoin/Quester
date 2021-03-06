#pragma once

#include <QtCore/QObject>
#include <public/selectcharacterwidget.h>

#include "ExecData.hpp"
#include "ItemData.hpp"

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
    ### Model used to remove an UE4 GameItem Class from a character
    Needs an UE4 generated GameItem Database before usage.
    */
    class RemoveItemModel : public NodeDataModel
    {
      Q_OBJECT

    public:
      RemoveItemModel();

      virtual
      ~RemoveItemModel() {}

    public:
      QString
      caption() const override
      {
        return QString("Remove Item");
      }

      QString
      name() const override
      {
        return QString("Remove Item");
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

      unsigned int
      nPorts(PortType portType) const override;

      NodeDataType
      dataType(PortType portType, PortIndex portIndex) const override;

      std::shared_ptr<NodeData>
      outData(PortIndex port) override;

      void
      setInData(std::shared_ptr<NodeData>, int) override;

     QWidget *
     embeddedWidget() override { return _getItemWidget; }

     NodeValidationState
     validationState() const override;

     QString
     validationMessage() const override;

     void
     compute(bool isQuestConnected);

    private:

     SelectCharacterWidget *
     _getItemWidget;

     NodeValidationState _modelValidationState = NodeValidationState::Warning;
     QString _modelValidationError = QString("Missing or incorrect inputs");
    };
}

