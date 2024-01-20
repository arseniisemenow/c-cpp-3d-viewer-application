#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QVector3D>
#include <QVector4D>

namespace constants {
inline constexpr int numberOfVertexCoordinates{3};
inline constexpr int numberOfEdgePoints{2};

inline constexpr float defaultAzimuthAngle{-90.0f};
inline constexpr float defaultElevationAngle{0.0f};
inline constexpr float defaultFieldOfView{45.0f};
inline constexpr float defaultPerspectiveNearPlane{0.1f};
inline constexpr float defaultPerspectiveFarPlane{10000.0f};
inline constexpr float defaultOrthographicNearPlane{-1000.0f};
inline constexpr float defaultOrthographicFarPlane{1000.0f};
inline constexpr float defaultOrthographicScale{2.0f};
inline constexpr float defaultEdgeWidth{1.0f};
inline constexpr float defaultPointSize{1.0f};
inline constexpr float defaultSensitivity{0.2f};
inline constexpr float defaultZoomSpeed{0.0075f};
inline constexpr QVector4D defaultBackgroundColor{0.0f, 0.0f, 0.0f, 1.0f};
inline constexpr QVector3D defaultEdgeColor{1.0f, 1.0f, 1.0f};
inline constexpr QVector3D defaultPointColor{1.0f, 1.0f, 1.0f};
inline constexpr QVector3D defaultTranslation{0.0f, 0.0f, 0.0f};
inline constexpr QVector3D defaultRotationAngles{0.0f, 0.0f, 0.0f};
inline constexpr QVector3D defaultScaling{1.0f, 1.0f, 1.0f};
inline constexpr float defaultCameraSpeed{0.05f};
inline constexpr QVector3D defaultCameraPosition{0.0f, 0.0f, -5.0f};
inline constexpr QVector3D defaultFrontVector{0.0f, 0.0f, 1.0f};
inline constexpr QVector3D worldUpVector{0.0f, 1.0f, 0.0f};

inline constexpr float orthoScaleChangeSpeed{0.002f};
inline constexpr float inertialMovementDampingFactor{0.95f};
inline constexpr float inertialMovementThreshold{0.01f};

inline constexpr float minimumFieldOfView{1.0f};
inline constexpr float maximumFieldOfView{80.0f};
inline constexpr float maximumElevationAngle{89.0f};
inline constexpr float minimumOrthographicScale{1.0f};
inline constexpr float minimumDistanceToObjectCenter{2.0f};

inline constexpr QVector3D xAxis{1.0f, 0.0f, 0.0f};
inline constexpr QVector3D yAxis{0.0f, 1.0f, 0.0f};

inline constexpr int millisecondsPerFrame{16};

inline constexpr int defaultWidthForScreenCast{640};
inline constexpr int defaultHeightForScreenCast{480};
inline constexpr int defaultDelayForScreenCast{100};
inline constexpr int defaultDurationScreenCast{5};

} // namespace constants

#endif // CONSTANTS_H
