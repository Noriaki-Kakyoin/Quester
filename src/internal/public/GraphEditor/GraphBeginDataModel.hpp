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
    ### Model used to begin a Quest/Dialogue graph
    In conjuction with GraphFinishDataModel it is an essential and non skippable node of every graph.
    */
    class GraphBeginDataModel : public NodeDataModel
    {
      Q_OBJECT

    public:
      GraphBeginDataModel();

      virtual
      ~GraphBeginDataModel() {}

    public:
      QString
      caption() const override
      {
        return QString("Execute Graph");
      }

      QString
      name() const override
      {
        return QString("Execute Graph");
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
