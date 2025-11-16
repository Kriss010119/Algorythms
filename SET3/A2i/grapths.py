import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df_main = pd.read_csv('sort_res.csv')
df_threshold = pd.read_csv('threshold.csv')
rnd_arr = df_main[df_main['type'] == 'random']
fig, axes = plt.subplots(2, 3, figsize=(18, 10))

for threshold in rnd_arr['threshold'].unique():
    if threshold == 0:
        label = 'Standard Merge'
        line_style = 'k-'
        line_width = 3
    else:
        label = f'Hybrid k={threshold}'
        line_style = '--'
        line_width = 1.5
    data = rnd_arr[rnd_arr['threshold'] == threshold]
    axes[0,0].plot(data['size'], data['time'], line_style, linewidth=line_width, label=label)
axes[0,0].set_title('Случайные массивы')
axes[0,0].set_xlabel('Размер массива')
axes[0,0].set_ylabel('Время (мс)')
axes[0,0].legend(fontsize=8)
axes[0,0].grid(True, alpha=0.3)

reverse_data = df_main[df_main['type'] == 'reverse']
for threshold in reverse_data['threshold'].unique():
    if threshold == 0:
        label = 'Standard Merge'
        line_style = 'k-'
        line_width = 3
    else:
        label = f'Hybrid k={threshold}'
        line_style = '--'
        line_width = 1.5
    data = reverse_data[reverse_data['threshold'] == threshold]
    axes[0,1].plot(data['size'], data['time'], line_style, linewidth=line_width, label=label)
axes[0,1].set_title('Обратно отсортированные массивы')
axes[0,1].set_xlabel('Размер массива')
axes[0,1].set_ylabel('Время (мс)')
axes[0,1].legend(fontsize=8)
axes[0,1].grid(True, alpha=0.3)

almost_data = df_main[df_main['type'] == 'almost_sorted']
for threshold in almost_data['threshold'].unique():
    if threshold == 0:
        label = 'Standard Merge'
        line_style = 'k-'
        line_width = 3
    else:
        label = f'Hybrid k={threshold}'
        line_style = '--'
        line_width = 1.5
    data = almost_data[almost_data['threshold'] == threshold]
    axes[0,2].plot(data['size'], data['time'], line_style, linewidth=line_width, label=label)
axes[0,2].set_title('Почти отсортированные массивы')
axes[0,2].set_xlabel('Размер массива')
axes[0,2].set_ylabel('Время (мс)')
axes[0,2].legend(fontsize=8)
axes[0,2].grid(True, alpha=0.3)

sizes = df_threshold['size'].unique()
for size in sizes:
    size_data = df_threshold[df_threshold['size'] == size]
    axes[1,0].plot(size_data['threshold'], size_data['time'], 'o-', label=f'Size {size}', markersize=5)
axes[1,0].set_title('Оптимальный порог переключения')
axes[1,0].set_xlabel('Порог k')
axes[1,0].set_ylabel('Время (мс)')
axes[1,0].legend()
axes[1,0].grid(True, alpha=0.3)

for array_type in df_main['type'].unique():
    type_data = df_main[df_main['type'] == array_type]
    st_time = type_data[type_data['threshold'] == 0].set_index('size')['time']
    best_hybrid = type_data[type_data['threshold'] != 0].groupby('size')['time'].min()
    s = (st_time / best_hybrid).dropna()
    axes[1,1].plot(s.index, s.values, 'o-', label=array_type, markersize=3)
axes[1,1].set_title('Ускорение гибрида\n')
axes[1,1].set_xlabel('Размер массива')
axes[1,1].set_ylabel('Ускорения')
axes[1,1].legend()
axes[1,1].grid(True, alpha=0.3)


best_thresholds = []
for array_type in df_main['type'].unique():
    type_data = df_main[df_main['type'] == array_type]
    best_by_threshold = type_data[type_data['threshold'] != 0].groupby('threshold')['time'].mean()
    best_threshold = best_by_threshold.idxmin()
    best_time = best_by_threshold.min()
    best_thresholds.append((array_type, best_threshold, best_time))
threshold_types, threshold_values, threshold_times = zip(*best_thresholds)
bars = axes[1,2].bar(threshold_types, threshold_times, color=['skyblue', 'lightcoral', 'lightgreen'])
axes[1,2].set_title('Среднее время для массивов')
axes[1,2].set_ylabel('Время (мс)')
for i, (bar, threshold) in enumerate(zip(bars, threshold_values)):
    height = bar.get_height()
    axes[1,2].text(bar.get_x() + bar.get_width()/2., height + 50,
                  f'k={threshold}', ha='center', va='bottom', fontweight='bold')

plt.tight_layout()
plt.savefig('analize.png', dpi=300, bbox_inches='tight')
plt.show()