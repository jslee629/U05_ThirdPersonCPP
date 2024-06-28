#include "CEnemyHealthWidget.h"
#include "Components/ProgressBar.h"

void UCEnemyHealthWidget::ApplyHealth_Implementation(float InCurHealth, float InMaxHealth)
{
	HealthBar->SetPercent(InCurHealth/InMaxHealth);
}
