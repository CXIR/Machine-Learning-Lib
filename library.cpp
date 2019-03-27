#include <iostream>
#include <cstdlib>

extern "C"
{
    static double * w;

    double* Initialize(int valuesUsedByModel)
    {
        w = new double[valuesUsedByModel];
        for (int i = 0; i < valuesUsedByModel; i++) {
            w[i] = -1 + (rand() % (3));
        }
        return w;
    }

    double Sign (double result)
    {
        return (result > 0) ? 1 : -1;
    }

    double Predict(double *w, double* inputk, int valuesUsedByModel)
    {
        double result = w[0];

        for (int i = 0; i < valuesUsedByModel; i++)
        {
            result += w[i + 1] * inputk[i];
        }

        return Sign(result);
    }

    void Train(double* w, double inputs[], int valuesUsedByModel, int modelsTested, double valuesExpected[], double learningStep, int iteration)
    {
        for (int i = 0; i < iteration; i++)
        {
            for (int k = 0; k < modelsTested; k++)
            {
                double* inputk = inputs + k * valuesUsedByModel;

                double gxk = Predict(w, inputk, valuesUsedByModel);

                w[0] = w[0] + learningStep * (valuesExpected[k] - gxk) * 1;

                for (int j = 0; j < valuesUsedByModel; j++)
                {
                    w[j + 1] = w[j + 1] + learningStep * (valuesExpected[k] - gxk) * inputs[j];
                }
            }
        }
    }

    double* GetW()
    {
        return w;
    }
}
