import 'dart:io';

Future<void> main(List<String> argv) async {
  for(final fileName in argv) {
    final file = File(fileName);
    final data = await file.readAsString();
    Blocks initial = parseBlocks(data);
    print("Solving $fileName");
    print("Part 1: ${part1(initial)}");
    print("Part 2: ${part2(initial)}");
  }
  
}

int part1(Blocks initial) {
  var states = getBlocksStates(initial);
  return states.length - 1;
}

int part2(Blocks initial) {
  final states = getBlocksStates(initial);
  return states.length - states.indexOf(states.last) - 1;
}

List<Blocks> getBlocksStates(Blocks initial) {
  final seen = <Blocks>{};
  final states = <Blocks>[];
  var current = initial;

  while(!seen.contains(current)) {
    seen.add(current);
    states.add(current);

    final newBlocks = List<int>.from(current.blocks);
    final max = findMax(newBlocks);

    var currMemory = max.$1;
    var currIndex = max.$2;
    newBlocks[currIndex] = 0;

    while(currMemory > 0) {
      currIndex++;
      if(currIndex >= newBlocks.length) {
        currIndex = 0;
      }

      newBlocks[currIndex]++;
      currMemory--;
    }

    current = Blocks(newBlocks);
  }

  states.add(current);
  return states;
}

(int value, int index) findMax(List<int> list) {
  var index = 0;
  var max = list[0];
  for(var i = 0; i < list.length; i++) {
    if(list[i] > max) {
      max = list[i];
      index = i;
    }
  }

  return (max, index);
}

Blocks parseBlocks(String data) {
  return Blocks(data.split(' ').map((e) => int.parse(e)));
}

class Blocks {
  final Iterable<int> blocks;

  Blocks(this.blocks);

  Blocks.from(Blocks other) : this.blocks = List.from(other.blocks);

  @override
  bool operator ==(covariant Blocks other) {
    var iter = this.blocks.iterator;
    var otherIter = other.blocks.iterator;

    var iterCond = iter.moveNext();
    var otherIterCond = otherIter.moveNext();

    while (iterCond && otherIterCond) {
      if (iter.current != otherIter.current) {
        return false;
      }

      iterCond = iter.moveNext();
      otherIterCond = otherIter.moveNext();
    }

    if (iterCond || otherIterCond) {
      return false;
    }

    return true;
  }

  @override
  int get hashCode {
    var hash = 0;
    for (final block in blocks) {
      hash = (hash << 5) ^ block * 31;
    }
    return hash;
  }
}
