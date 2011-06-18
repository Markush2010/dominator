/**
 * @author Markus Holtermann
 * @date Jun 17, 2011
 * @file gui/qutils.hpp
 */

#ifndef QUTILSS_HPP_
#define QUTILSS_HPP_

#include <QtGui/QAction>
#include <simulation/simulation.hpp>

namespace gui {

/**
 *
 */
class QObjectAction: public QAction {
Q_OBJECT
public:
	/**
	 *
	 */
	QObjectAction(const QString &text, sim::__Object::Type type, QWidget* parent = 0);
	sim::__Object::Type getType();

private:
	sim::__Object::Type m_type;

private slots:
	void sendObjectActionTriggered();

signals:
	void triggered(sim::__Object::Type);
};

inline sim::__Object::Type QObjectAction::getType()
{
	return m_type;
}

}
#endif /* QUTILSS_HPP_ */
