#pragma once

#include <QGraphicsObject>
#include "../interfaces/json.h"
#include "../types.h"
#include "../settings.h"

namespace QSchematic {

    class Scene;

    class Item : public QGraphicsObject, public Json
    {
        Q_OBJECT
        Q_DISABLE_COPY(Item)

    public:
        enum ItemType {
            NodeType      = QGraphicsItem::UserType + 1,
            WireType,
            ConnectorType,
            LabelType,

            QSchematicItemUserType = QGraphicsItem::UserType + 100
        };
        Q_ENUM(ItemType)

        const QString JSON_ID_STRING = QStringLiteral("item type id");

        Item(int type, QGraphicsItem* parent = nullptr);
        virtual ~Item() override = default;

        virtual QJsonObject toJson() const override;
        virtual bool fromJson(const QJsonObject& object) override;

        int type() const final;
        void setGridPoint(const QPoint& newGridPoint);
        void setGridPoint(int x, int y);
        void setGridPointX(int x);
        void setGridPointY(int y);
        QPoint gridPoint() const;
        int gridPointX() const;
        int gridPointY() const;
        QPointF scenePoint() const;
        qreal scenePointX() const;
        qreal scenePointY() const;
        void setSettings(const Settings& settings);
        const Settings& settings() const;
        void setMovable(bool enabled);
        bool isMovable() const;
        void setSnapToGrid(bool enabled);
        bool snapToGrid() const;
        void setHighlighted(bool isHighlighted);
        void setHighlightEnabled(bool enabled);
        bool highlightEnabled() const;
        QPixmap toPixmap(qreal scale = 1.0);
        virtual void update();
        virtual QWidget* popupInfobox() const;

    signals:
        void moved(Item& item, const QVector2D& movedBy);
        void showPopup(const Item& item);
        void highlightChanged(const Item& item, bool isHighlighted);

    protected:
        Settings _settings;

        void addTypeIdentifierToJson(QJsonObject& object) const;

        bool isHighlighted() const;
        virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
        virtual void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
        virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
        virtual QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value) override;

    private slots:
        void timerTimeout();
        void posChanged();

    private:
        int _type;
        bool _snapToGrid;
        bool _highlightEnabled;
        bool _highlighted;
        QPoint _oldGridPoint;
        QTimer* _hoverTimer;
    };

}
