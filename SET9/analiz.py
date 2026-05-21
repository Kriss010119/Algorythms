import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
from matplotlib import rcParams

rcParams['font.size'] = 11
rcParams['figure.dpi'] = 150

def load_csv(file='sorting_res.csv'):
    df = pd.read_csv(file)
    df = df[df['Sorted'] == 'yes']
    
    algorithm_names = {
        'QuickSort': 'Quick Sort',
        'MergeSort': 'Merge Sort', 
        'TernarQS': 'Ternary Quick Sort',
        'StrMerge': 'String Merge Sort',
        'MSD_Radix': 'MSD Radix Sort',
        'MSD_Radix_QS': 'MSD Radix + Ternary QS'
    }
    
    data_types = ['Random', 'Reverse', 'Nearly']
    data_type_labels = {
        'Random': 'Случайные данные',
        'Reverse': 'Обратно отсортированные',
        'Nearly': 'Почти отсортированные'
    }
    
    colors = {
        'Quick Sort': '#E41A1C',
        'Merge Sort': '#377EB8',
        'Ternary Quick Sort': '#4DAF4A',
        'String Merge Sort': '#984EA3',
        'MSD Radix Sort': '#FF7F00',
        'MSD Radix + Ternary QS': '#A65628'
    }
    
    markers = ['o', 's', '^', 'D', 'v', '<', '>', 'p', '*', 'h']
    
    fig, axes = plt.subplots(2, 3, figsize=(17, 10))
    fig.suptitle('Сравнение алгоритмов сортировки строк', fontsize=14, fontweight='bold')
    
    for idx, data_type in enumerate(data_types):
        ax_comparisons = axes[0, idx]
        ax_time = axes[1, idx]
        
        marker_idx = 0
        for algo_short, algo_full in algorithm_names.items():
            algo_data = df[df['Algorithm'].str.contains(f'{algo_short}_{data_type}')]
            if algo_data.empty:
                continue
            
            algo_data = algo_data.sort_values('Size')
            sizes = algo_data['Size'].values
            comparisons = algo_data['Comparisons'].values
            times = algo_data['Time_ms'].values
            if algo_short == 'MSD_Radix' and (comparisons == 0).all():
                continue
            color = colors.get(algo_full, '#000000')
            marker = markers[marker_idx % len(markers)]
            
            ax_comparisons.plot(sizes, comparisons, 
                              label=algo_full, 
                              color=color,
                              linewidth=2, 
                              marker=marker, 
                              markersize=4,
                              markevery=5)
            ax_time.plot(sizes, times, 
                        label=algo_full, 
                        color=color,
                        linewidth=2, 
                        marker=marker, 
                        markersize=4,
                        markevery=5)
            marker_idx += 1
        
        ax_comparisons.set_title(f'{data_type_labels[data_type]} — Сравнения', fontsize=11)
        ax_comparisons.set_xlabel('Размер массива')
        ax_comparisons.set_ylabel('Количество посимвольных сравнений')
        ax_comparisons.grid(True, alpha=0.3, linestyle='--')
        ax_comparisons.legend(loc='upper left', fontsize=8, framealpha=0.9)
        ax_time.set_title(f'{data_type_labels[data_type]} — Время', fontsize=11)
        ax_time.set_xlabel('Размер массива')
        ax_time.set_ylabel('Время (мс)')
        ax_time.grid(True, alpha=0.3, linestyle='--')
        ax_time.legend(loc='upper left', fontsize=8, framealpha=0.9)
    
    plt.tight_layout()
    plt.savefig('sorting_analysis.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    return df

if __name__ == "__main__":
    file = 'sorting_res.csv'
    df = load_csv(file)