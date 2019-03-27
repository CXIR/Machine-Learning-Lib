#include <iostream>
#include <cstdlib>

extern "C"
{
    int Return42()
    {
        return 42;
    }

    double* Initialize(int valuesUsedByModel)
    {
        double* w = new double[valuesUsedByModel];
        for (int i = 0; i < valuesUsedByModel; i++) {
            w[i] = -1 + (rand() % (3));
        }
        return w;
    }

    int Sign(double result)
    {
        return (result > 0) ? 1 : -1;
    }

    int Predict(double* w, double* inputk, int valuesUsedByModel)
    {
        double result = w[0];

        for (int i = 0; i < valuesUsedByModel; i++)
        {
            result += w[i + 1] * inputk[i];
        }

        return Sign(result);
    }

    void Train(double* w, double* inputs, int valuesUsedByModel, int modelsTested, double* output, double learningStep, int iteration)
    {
        for (int i = 0; i < iteration; i++)
        {
            for (int k = 0; k < modelsTested; k++)
            {
                double* inputk = inputs + k * valuesUsedByModel;

                int gxk = Predict(w, inputk, valuesUsedByModel);

                w[0] = w[0] + learningStep * (output[k] - gxk) * 1;

                for (int j = 0; j < valuesUsedByModel; j++)
                {
                    w[j + 1] = w[j + 1] + learningStep * (output[k] - gxk) * inputk[j];
                }
            }
        }
    }
}
