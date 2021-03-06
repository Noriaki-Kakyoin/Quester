#pragma once

#include <QtCore/QObject>
#include <QtWidgets/QTextEdit>

#include "ExecData.hpp"

#include <nodes/NodeDataModel>

#include <iostream>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataModel;

namespace GraphEditor {
    /*!
    ### Model used to spawn one or more actor of class at a certain location
    Needs a generated UE4 Character Database before usage.
    */
    class SpawnAtLocationModel : public NodeDataModel
    {
      Q_OBJECT

    public:
      SpawnAtLocationModel();

      virtual
      ~SpawnAtLocationModel() {}

    public:
      QString
      caption() const override
      {
        return QString("Spawn At Location");
      }

      QString
      name() const override
      {
        return QString("Spawn At Location");
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
      { }

     QWidget *
     embeddedWidget() override { return nullptr; }
    };
}
