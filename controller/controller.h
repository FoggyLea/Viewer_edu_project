/**
 * @file controller.h
 * @brief Заголовочный файл для класса Controller.
 *
 * В этом файле определен класс Controller, который управляет логикой
 * взаимодействия между моделью и представлением.
 *
 * Основные задачи:
 * - Прием сигналов от представления и изменение модели (перемещение, вращение,
 * масштабирование).
 * - Загрузка модели из файла и передача данных в представление.
 * - Обновление представления после применения изменений в модели.
 *
 * Используется паттерн "наблюдатель", где Controller является подписчиком на
 * сигналы от View.
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <QObject>

#include "../model/model.h"
#include "axis.h"

namespace s21 {

class View;

/**
 * @brief Класс контроллера, который связывает модель и представление.
 *
 * Контроллер принимает сигналы от представления, такие как изменения положения,
 * вращения и масштаба, и применяет эти изменения к модели. Он также
 * обрабатывает загрузку модели и передачу данных в представление. Контроллер
 * использует паттерн "наблюдатель" для связи с представлением через сигналы и
 * слоты.
 */
class Controller : public QObject {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор контроллера.
   *
   * Создает объект контроллера и устанавливает связи с представлением и
   * моделью.
   *
   * @param model Указатель на объект модели.
   * @param view Указатель на объект представления.
   */
  explicit Controller(Model* model, View* view);

  /**
   * @brief Деструктор контроллера.
   *
   * Очищает ресурсы контроллера.
   */
  ~Controller();

  /**
   * @brief Загружает модель из файла и передает данные в представление.
   *
   * Этот метод загружает модель из указанного файла и передает информацию о
   * вершинах и гранях модели в представление для отображения.
   *
   * @param path Путь к файлу модели.
   */
  void LoadModel(const std::string& path);

 private:
  Model* model_;              ///< Указатель на модель.
  View* view_;                ///< Указатель на представление.
  TransformParametrs delta_;  ///< Параметры трансформации модели.

 private slots:

  /**
   * @brief Обновляет модель с учетом трансформаций.
   *
   * Применяет изменения трансформации (перемещения, вращения, масштабирования)
   * к модели.
   */
  void UpdateModel();

  /**
   * @brief Обрабатывает изменения перемещения модели по указанной оси.
   *
   * Этот слот вызывается, когда происходит изменение положения модели.
   *
   * @param value Значение изменения.
   * @param axis Ось, по которой произошло изменение.
   */
  void OnMoveChanged(float value, Axis axis);

  /**
   * @brief Обрабатывает изменения масштаба модели.
   *
   * Этот слот вызывается, когда происходит изменение масштаба модели.
   * Масштабируется модель одинаково по всем осям.
   *
   * @param value Значение масштаба.
   */
  void OnScaleChanged(float value);

  /**
   * @brief Обрабатывает изменения угла вращения модели по указанной оси.
   *
   * Этот слот вызывается, когда происходит изменение угла вращения модели.
   * Угол преобразуется в радианы для применения.
   *
   * @param value Значение угла вращения.
   * @param axis Ось, вокруг которой произошло вращение.
   */
  void OnRotateChanged(float value, Axis axis);
};

}  // namespace s21
#endif  // CONTROLLER_H_
