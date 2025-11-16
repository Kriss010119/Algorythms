import pandas as pd
import matplotlib.pyplot as plt

quick_data = pd.read_csv('quick.csv')
hybrid_data = pd.read_csv('hibrid.csv')

plt.figure(figsize=(12, 8))
for data_type in quick_data['type'].unique():
    subset = quick_data[quick_data['type'] == data_type]
    plt.plot(subset['size'], subset['time'], label=data_type, linewidth=2)
plt.xlabel('Array Size')
plt.ylabel('Time (mc)')
plt.title('Quick Sort')
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig('quick.png', dpi=300, bbox_inches='tight')
plt.show()

data_types = hybrid_data['type'].unique()
thresholds = hybrid_data['threshold'].unique()
for data_type in data_types:
    plt.figure(figsize=(12, 8))
    type_data = hybrid_data[hybrid_data['type'] == data_type]
    for threshold in thresholds:
        subset = type_data[type_data['threshold'] == threshold]
        plt.plot(subset['size'], subset['time'], 
                label=f'threshold={threshold}', linewidth=2, marker='o', markersize=4)
    plt.xlabel('Array Size')
    plt.ylabel('Time (mc)')
    plt.title(f'Hibrid Sort - {data_type}')
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    plt.savefig(f'hibrid_{data_type}.png', dpi=300, bbox_inches='tight')
    plt.show()

plt.figure(figsize=(12, 8))
for data_type in data_types:
    quick_subset = quick_data[quick_data['type'] == data_type]
    plt.plot(quick_subset['size'], quick_subset['time'], 
             label=f'Quick Sort ({data_type})', linewidth=2, linestyle='--')
    hybrid_type_data = hybrid_data[hybrid_data['type'] == data_type]
    best_hybrid = hybrid_type_data.groupby('size')['time'].min().reset_index()
    plt.plot(best_hybrid['size'], best_hybrid['time'], 
             label=f'Hibrid ({data_type})', linewidth=2)
plt.xlabel('Array Size')
plt.ylabel('Time (mc)')
plt.title('Quick Sort vs Hibrid Sort')
plt.legend()
plt.grid(True, alpha=0.3)
plt.tight_layout()
plt.savefig('hibridVSquick.png', dpi=300, bbox_inches='tight')
plt.show()