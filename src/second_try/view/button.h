#ifndef BUTTON_H_
#define BUTTON_H_

#include <QToolButton>

/**
 * @class Button
 * @brief A custom Qt button widget with a specific text label and size.
 *
 * The `Button` class is designed to create custom push buttons in a Qt
 * application. It inherits from `QToolButton` and provides a constructor to set
 * the button's text label and a preferred size.
 */
class Button : public QToolButton {
  Q_OBJECT

 public:
  /**
   * @brief Constructor for the Button class.
   *
   * Initializes the button with the specified text label and an optional parent
   * widget. The button is set to have a preferred width and a fixed height.
   *
   * @param text The text label to display on the button.
   * @param parent An optional parent widget. Default is nullptr.
   */
  explicit Button(const QString &text, QWidget *parent = nullptr);

  /**
   * @brief Get the preferred size of the button.
   *
   * This function overrides the default size hint to specify the preferred size
   * of the button, setting a fixed width and fixed height.
   *
   * @return The preferred size of the button.
   */
  QSize sizeHint() const override;
};

#endif  // BUTTON_H_