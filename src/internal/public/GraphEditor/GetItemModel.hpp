#pragma once

#include <QtCore/QObject>
#include <public/getitemwidget.h>

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
    ### Model used to retrieve a UE4 GameItem Class
    Needs to load a GameItem Database first to display options on the widget.
    */
    class GetItemModel : public NodeDataModel
    {
      Q_OBJECT

    public:
      GetItemModel();

      virtual
      ~GetItemModel() {}

    public:
      QString
      caption() const override
      {
        return QString("Get Item");
      }

      QString
      name() const override
      {
        return QString("Get Item");
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
      setInData(std::shared_ptr<NodeData>, int) override
      {}

     QWidget *
     embeddedWidget() override { return _getItemWidget; }

    private:

     GetItemWidget *
     _getItemWidget;
    };
}
