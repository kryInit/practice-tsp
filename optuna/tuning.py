import optuna
import subprocess

def objective(trial):

    TEMP_RADIX = trial.suggest_uniform('temp radix', 50, 3000)
    PROBABILITY_COEF = trial.suggest_uniform('probability coefficient', 0.000001, 1)
    
    total_dist = float(subprocess.check_output(['./route_builder', str(TEMP_RADIX), str(PROBABILITY_COEF)]))

    print('temp radix: %1.3f, probability coefficient: %1.3f, total_dist: %1.3f' % (TEMP_RADIX, PROBABILITY_COEF, total_dist))

    return total_dist

study = optuna.create_study()
study.optimize(objective, n_trials=10000)

print()
print('best parameters: ', study.best_params)
print('minimum total dist: ', study.best_value)
print()
print(study.best_trial)


