#include "Math.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include "../Time/Stopwatch.hpp"

#include "../Logging.hpp"

namespace dex
{
	namespace Math
	{
		glm::vec3 decomposeTransformToTranslation(const glm::mat4& matrix)
		{
			using namespace glm;
			using T = float;

			mat4 LocalMatrix(matrix);

			// Normalize the matrix.
			if (epsilonEqual(LocalMatrix[3][3], static_cast<T>(0), epsilon<T>()))
				DEX_LOG_ERROR("<dex::Math::decomposeTransformToTranslation()>: epsilonEqual check returned true.");

			// First, isolate perspective.  This is the messiest.
			if (
				epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
			{
				// Clear the perspective partition
				LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
				LocalMatrix[3][3] = static_cast<T>(1);
			}

			// Next take care of translation (easy).
			return vec3(LocalMatrix[3]);
		}

		glm::quat decomposeTransformToOrientation(const glm::mat4& matrix)
		{
			using namespace glm;
			using T = float;

			mat4 LocalMatrix(matrix);

			// Normalize the matrix.
			if (epsilonEqual(LocalMatrix[3][3], static_cast<T>(0), epsilon<T>()))
				DEX_LOG_ERROR("<dex::Math::decomposeTransformToTranslation()>: epsilonEqual check returned true.");

			// First, isolate perspective.  This is the messiest.
			if (
				epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
			{
				// Clear the perspective partition
				LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
				LocalMatrix[3][3] = static_cast<T>(1);
			}

			LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

			vec3 Row[3], Pdum3;

			// Now get scale and shear.
			for (length_t i = 0; i < 3; ++i)
				for (length_t j = 0; j < 3; ++j)
					Row[i][j] = LocalMatrix[i][j];

			Row[0] = detail::scale(Row[0], static_cast<T>(1));
			Row[1] = detail::scale(Row[1], static_cast<T>(1));
			Row[2] = detail::scale(Row[2], static_cast<T>(1));

			// At this point, the matrix (in rows[]) is orthonormal.
			// Check for a coordinate system flip.  If the determinant
			// is -1, then negate the matrix and the scaling factors.
			Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
			if (dot(Row[0], Pdum3) < 0)
			{
				for (length_t i = 0; i < 3; i++)
				{
					Row[i] *= static_cast<T>(-1);
				}
			}

			glm::quat ret_orientation;

			int i, j, k = 0;
			T root, trace = Row[0].x + Row[1].y + Row[2].z;
			if (trace > static_cast<T>(0))
			{
				root = sqrt(trace + static_cast<T>(1.0));
				ret_orientation.w = static_cast<T>(0.5) * root;
				root = static_cast<T>(0.5) / root;
				ret_orientation.x = root * (Row[1].z - Row[2].y);
				ret_orientation.y = root * (Row[2].x - Row[0].z);
				ret_orientation.z = root * (Row[0].y - Row[1].x);
			} // End if > 0
			else
			{
				static int Next[3] = { 1, 2, 0 };
				i = 0;
				if (Row[1].y > Row[0].x) i = 1;
				if (Row[2].z > Row[i][i]) i = 2;
				j = Next[i];
				k = Next[j];

				root = sqrt(Row[i][i] - Row[j][j] - Row[k][k] + static_cast<T>(1.0));

				ret_orientation[i] = static_cast<T>(0.5) * root;
				root = static_cast<T>(0.5) / root;
				ret_orientation[j] = root * (Row[i][j] + Row[j][i]);
				ret_orientation[k] = root * (Row[i][k] + Row[k][i]);
				ret_orientation.w = root * (Row[j][k] - Row[k][j]);
			} // End if <= 0

			return ret_orientation;
		}

		glm::vec3 decomposeTransformToScale(const glm::mat4& matrix)
		{
			using namespace glm;
			using T = float;

			mat4 LocalMatrix(matrix);

			// Normalize the matrix.
			if (epsilonEqual(LocalMatrix[3][3], static_cast<T>(0), epsilon<T>()))
				DEX_LOG_ERROR("<dex::Math::decomposeTransformToTranslation()>: epsilonEqual check returned true.");

			// First, isolate perspective.  This is the messiest.
			if (
				epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
			{
				// Clear the perspective partition
				LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
				LocalMatrix[3][3] = static_cast<T>(1);
			}

			LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

			vec3 Row[3];

			// Now get scale and shear.
			for (length_t i = 0; i < 3; ++i)
				for (length_t j = 0; j < 3; ++j)
					Row[i][j] = LocalMatrix[i][j];

			Row[0] = detail::scale(Row[0], static_cast<T>(1));
			Row[1] = detail::scale(Row[1], static_cast<T>(1));
			Row[2] = detail::scale(Row[2], static_cast<T>(1));

			glm::vec3 ret_scale;
			
			ret_scale.x = length(Row[0]);
			ret_scale.y = length(Row[1]);
			ret_scale.z = length(Row[2]);

			return ret_scale;
		}

		bool decomposeTransform(const glm::mat4& matrix, glm::vec3* translation, glm::quat* orientation, glm::vec3* scale)
		{
			using namespace glm;
			using T = float;

			mat4 LocalMatrix(matrix);

			// Normalize the matrix.
			if (epsilonEqual(LocalMatrix[3][3], static_cast<T>(0), epsilon<T>()))
				return false;

			// First, isolate perspective.  This is the messiest.
			if (
				epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
			{
				// Clear the perspective partition
				LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
				LocalMatrix[3][3] = static_cast<T>(1);
			}

			// Next take care of translation (easy).
			if (translation != nullptr)
				*translation = vec3(LocalMatrix[3]);

			LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

			vec3 Row[3], Pdum3;

			// Now get scale and shear.
			for (length_t i = 0; i < 3; ++i)
				for (length_t j = 0; j < 3; ++j)
					Row[i][j] = LocalMatrix[i][j];

			Row[0] = detail::scale(Row[0], static_cast<T>(1));
			Row[1] = detail::scale(Row[1], static_cast<T>(1));
			Row[2] = detail::scale(Row[2], static_cast<T>(1));

			if (scale != nullptr)
			{
				(*scale).x = length(Row[0]);
				(*scale).y = length(Row[1]);
				(*scale).z = length(Row[2]);
			}

			// At this point, the matrix (in rows[]) is orthonormal.
			// Check for a coordinate system flip.  If the determinant
			// is -1, then negate the matrix and the scaling factors.
			Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
			if (dot(Row[0], Pdum3) < 0)
			{
				for (length_t i = 0; i < 3; i++)
				{
					if (scale != nullptr)
						(*scale)[i] *= static_cast<T>(-1);

					Row[i] *= static_cast<T>(-1);
				}
			}

			// Now, get the rotations out, as described in the gem.

			// FIXME - Add the ability to return either quaternions (which are
			// easier to recompose with) or Euler angles (rx, ry, rz), which
			// are easier for authors to deal with. The latter will only be useful
			// when we fix https://bugs.webkit.org/show_bug.cgi?id=23799, so I
			// will leave the Euler angle code here for now.

			// ret.rotateY = asin(-Row[0][2]);
			// if (cos(ret.rotateY) != 0) {
			//     ret.rotateX = atan2(Row[1][2], Row[2][2]);
			//     ret.rotateZ = atan2(Row[0][1], Row[0][0]);
			// } else {
			//     ret.rotateX = atan2(-Row[2][0], Row[1][1]);
			//     ret.rotateZ = 0;
			// }

			if (orientation != nullptr)
			{
				int i, j, k = 0;
				T root, trace = Row[0].x + Row[1].y + Row[2].z;
				if (trace > static_cast<T>(0))
				{
					root = sqrt(trace + static_cast<T>(1.0));
					(*orientation).w = static_cast<T>(0.5) * root;
					root = static_cast<T>(0.5) / root;
					(*orientation).x = root * (Row[1].z - Row[2].y);
					(*orientation).y = root * (Row[2].x - Row[0].z);
					(*orientation).z = root * (Row[0].y - Row[1].x);
				} // End if > 0
				else
				{
					static int Next[3] = { 1, 2, 0 };
					i = 0;
					if (Row[1].y > Row[0].x) i = 1;
					if (Row[2].z > Row[i][i]) i = 2;
					j = Next[i];
					k = Next[j];

					root = sqrt(Row[i][i] - Row[j][j] - Row[k][k] + static_cast<T>(1.0));

					(*orientation)[i] = static_cast<T>(0.5) * root;
					root = static_cast<T>(0.5) / root;
					(*orientation)[j] = root * (Row[i][j] + Row[j][i]);
					(*orientation)[k] = root * (Row[i][k] + Row[k][i]);
					(*orientation).w = root * (Row[j][k] - Row[k][j]);
				} // End if <= 0
			}

			return true;
		}
	}
}
